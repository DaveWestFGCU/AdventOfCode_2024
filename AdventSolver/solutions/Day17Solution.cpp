/** Dev: Dave West
 * Date: December 17, 2024
 * Desc: Method definitions for the AoC 2024 day 17 puzzle.
**/

#include "Day17Solution.h"


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



long long Day17Solution::oneStarSolution()
{
    device.runInstructions();
    return std::stoll(device.getOutput());
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


long Day17Solution::Computer::combo(const long &operand) const
{
    switch(operand)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return operand;

        case 4:
            return registerA;

        case 5:
            return registerB;

        case 6:
            return registerC;
    }
}




void Day17Solution::Computer::runOpcode(const int &opCode, const long &operand)
{
    switch (opCode)
    {
        case 0:
            adv(combo(operand));
            break;

        case 1:
            bxl(operand);
            break;

        case 2:
            bst(combo(operand));
            break;

        case 3:
            jnz(operand);
            break;

        case 4:
            bxc();
            break;

        case 5:
            out(combo(operand));
            break;

        case 6:
            bdv(combo(operand));
            break;

        case 7:
            cdv(combo(operand));
            break;
    }

    if (opCode != 3)
        instructionPointer += 2;
}


/**
 * opcode 0: adv
 * @param comboOperand
 */
void Day17Solution::Computer::adv(const long comboOperand)
{
    registerA = static_cast<long>(registerA / std::pow(2, comboOperand));
}


/**
 * opcode 1: bxl
 * @param operand
 */
void Day17Solution::Computer::bxl(const long operand)
{
    registerB = registerB ^ operand;
}


/**
 * opcode 2: bst
 * @param comboOperand
 */
void Day17Solution::Computer::bst(const long comboOperand)
{
    registerB = comboOperand % 8;
}


/**
 * opcode 3: jnz
 * @param operand
 */
void Day17Solution::Computer::jnz(const long operand)
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
void Day17Solution::Computer::out(const long comboOperand)
{
    output += std::to_string(comboOperand % 8);
}


/**
 * opcode 6: bdv
 * @param comboOperand
 */
void Day17Solution::Computer::bdv(const long comboOperand)
{
    registerB = static_cast<int>(registerA / std::pow(2, comboOperand));
}


/**
 * opcode 7: cdv
 * @param comboOperand
 */
void Day17Solution::Computer::cdv(const long comboOperand)
{
    registerC = static_cast<long>(registerA / std::pow(2, comboOperand));
}


long long Day17Solution::twoStarSolution()
{
    int result {0};

    return result;
}
