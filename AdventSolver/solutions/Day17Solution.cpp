/** Dev: Dave West
 * Date: December 17, 2024
 * Desc: Method definitions for the AoC 2024 day 17 puzzle.
**/

#include "Day17Solution.h"
#include <cmath>
#include <iomanip>

Day17Solution::Day17Solution(const vector<string> &puzzleInput)
    : title("--- Day 17: Chronospatial Computer ---")
{
    parseDebugger(puzzleInput);
}


void Day17Solution::parseDebugger(const vector<string> &puzzleInput)
{
    int registerA = std::stoi(puzzleInput[0].substr(12, puzzleInput[0].length()-12));
    int registerB = std::stoi(puzzleInput[1].substr(12, puzzleInput[1].length()-12));
    int registerC = std::stoi(puzzleInput[2].substr(12, puzzleInput[2].length()-12));

    string instructions = puzzleInput[4].substr(9, puzzleInput[4].length()-9);
    vector<int> program;
    for (const auto &character : instructions)
    {
        if (character == ',')
            continue;

        program.push_back(character - '0');
    }

    device = Computer(registerA, registerB, registerC, program);
}



string Day17Solution::oneStarSolution()
{
    device.runInstructions();

    vector<int> rawOutput = device.getOutput();

    string textOutput;
    for (const auto &item : rawOutput)
        textOutput += std::to_string(item) + ",";

    return textOutput.substr(0,textOutput.length()-1);
}


void Day17Solution::Computer::runInstructions()
{
    bool halted {false};
    while (!halted)
    {
        int nextOperation = program[instructionPointer];
        int nextOperand = program[instructionPointer+1];
        runOpcode(nextOperation, nextOperand);

        if (instructionPointer >= program.size())
            halted = true;
    }
}


void Day17Solution::Computer::runInstructions(long long registerA)
{
    this->registerA = registerA;
    registerB = 0;
    registerC = 0;
    instructionPointer = 0;
    output.clear();

    bool halted {false};
    while (!halted)
    {
        int nextOperation = program[instructionPointer];
        int nextOperand = program[instructionPointer+1];
        runOpcode(nextOperation, nextOperand);

        if (instructionPointer >= program.size())
            halted = true;
    }
}



long long Day17Solution::Computer::combo(const int &operand) const
{
    switch(operand)
    {
        case 0:     return 0;
        case 1:     return 1;
        case 2:     return 2;
        case 3:     return 3;
        case 4:     return registerA;
        case 5:     return registerB;
        case 6:     return registerC;
        default:    return -2;
    }
}


void Day17Solution::Computer::runOpcode(const int &opCode, const int &operand)
{
    switch (opCode)
    {
        case 0:     adv(combo(operand));    break;
        case 1:     bxl(operand);           break;
        case 2:     bst(combo(operand));    break;
        case 3:     jnz(operand);           break;
        case 4:     bxc();                  break;
        case 5:     out(combo(operand));    break;
        case 6:     bdv(combo(operand));    break;
        case 7:     cdv(combo(operand));    break;
        default:    ;
    }

    if (opCode != 3)
        instructionPointer += 2;
}


/**
 * opcode 0: adv
 * @param comboOperand
 */
void Day17Solution::Computer::adv(const long long &comboOperand)
{
    registerA = static_cast<long long>(registerA / std::pow(2, comboOperand));
}


/**
 * opcode 1: bxl
 * @param operand
 */
void Day17Solution::Computer::bxl(const int &operand)
{
    registerB = registerB ^ operand;
}


/**
 * opcode 2: bst
 * @param comboOperand
 */
void Day17Solution::Computer::bst(const long long &comboOperand)
{
    registerB = comboOperand % 8;
}


/**
 * opcode 3: jnz
 * @param operand
 */
void Day17Solution::Computer::jnz(const int &operand)
{
    if (registerA == 0)
    {
        instructionPointer += 2;
        return;
    }

    instructionPointer = operand;
}


/**
 * opcode 4: bxc
 */
void Day17Solution::Computer::bxc()
{
    registerB = registerB ^ registerC;
}


/**
 * opcode 5: out
 * @param comboOperand
 */
void Day17Solution::Computer::out(const long long &comboOperand)
{
    output.push_back(comboOperand % 8);
}


/**
 * opcode 6: bdv
 * @param comboOperand
 */
void Day17Solution::Computer::bdv(const long long &comboOperand)
{
    registerB = static_cast<long long>(registerA / std::pow(2, comboOperand));
}


/**
 * opcode 7: cdv
 * @param comboOperand
 */
void Day17Solution::Computer::cdv(const long long &comboOperand)
{
    registerC = static_cast<long long>(registerA / std::pow(2, comboOperand));
}


string Day17Solution::twoStarSolution()
{
    return std::to_string(findOriginalRegisterA());
}


long long Day17Solution::findOriginalRegisterA()
{
    long long originalRegisterA { 0 };
    findDigit(0, device.getProgram().size()-1, originalRegisterA);
    return originalRegisterA;
}


bool Day17Solution::findDigit(const long long &n, const int &digit, long long &foundRegisterA)
{
    // BASE CASE: All digits have been found
    if (digit < 0)
    {
        foundRegisterA = n;
        return true;
    }

    // RECURSIVE CASE: Find the next digit.
    for (int digitValue = 0; digitValue < 8; digitValue++)
    {
        long long registerA = n + digitValue * std::pow(8,digit);
        device.runInstructions(registerA);

        if (device.getOutput()[digit] == device.getProgram()[digit])
        {
            if (findDigit(registerA, digit-1, foundRegisterA))
                return true;
        }
    }

    return false;
}

