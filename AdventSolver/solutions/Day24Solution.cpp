/** Dev: Dave West
 * Date: December 24, 2024
 * Desc: Method definitions for the AoC 2024 day Christmas Eve puzzle.
 *  Log: 12/24/24 - Completed one-star solution. Started work on two-star solution.
 *       12/28/24 - Completed two-star solution.
 */

#include "Day24Solution.h"

#include <sstream>
#include <cmath>
#include <set>

Day24Solution::Day24Solution(const vector<string> &puzzleInput)
    : title("--- Day 24: Crossed Wires ---")
{
    bool beforeLineBreak { true };
    for (const auto &line : puzzleInput)
    {
        if (line.empty())
        {
            beforeLineBreak = false;
            continue;
        }

        if (beforeLineBreak)
        {
            string wireLabel = line.substr(0,3);
            bool wireValue = line[5] - '0';
            inputWires[wireLabel] = wireValue;
        }
        else
        {
            auto instruction = split(line, ' ');
            gates.emplace_back(instruction[0], instruction[1], instruction[2], instruction[4]);
        }
    }
}


vector<string> Day24Solution::split(const string &stringToParse, const char &delimiter)
{
    std::stringstream ss(stringToParse);
    string token;

    vector<string> tokens;
    while (std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}


string Day24Solution::oneStarSolution()
{
    vector<Gate> unvisitedGates(gates);

    while (!unvisitedGates.empty())
    {
        auto end = unvisitedGates.end();
        for (auto gate = unvisitedGates.begin(); gate != end; ++gate)  //  Iterate through gates, we'll need the iterator to delete executed gates later
        {
            if (!inputWires.contains(gate->inputWire1))
                continue;
            if (!inputWires.contains(gate->inputWire2))
                continue;

            inputWires[gate->outputWire] = runGate(*gate);

            unvisitedGates.erase(gate);
        }
    }

    // Convert z-wires to value by label
    long long zValue { 0 };
    for (const auto &wire : inputWires)
    {
        if (wire.first[0] != 'z')
            continue;

        if (wire.second)
        {
            int zIndex = std::stoi(wire.first.substr(1,2));
            zValue += std::pow(2, zIndex);
        }
    }

    return std::to_string(zValue);
}


bool Day24Solution::runGate(const Gate &gate)
{
    if (gate.gate == "AND")
        return inputWires[gate.inputWire1] & inputWires[gate.inputWire2];

    if (gate.gate == "OR")
        return inputWires[gate.inputWire1] | inputWires[gate.inputWire2];

    if (gate.gate == "XOR")
        return inputWires[gate.inputWire1] ^ inputWires[gate.inputWire2];
}


/**
 * Rule 1: z-wires are outputs only from XORs (except the last one)
 * @return A list of output wires that do not behave appropriately for this rule.
 */
vector<string> Day24Solution::assessRule1()
{
    vector<string> badOutputWires;
    for (const auto &gate : gates)
    {
        if (gate.outputWire[0] == 'z' && gate.gate != "XOR" && gate.outputWire != "z45")
            badOutputWires.push_back(gate.outputWire);
    }

    return badOutputWires;
}


/**
 * Rule 2: Non-Z-outputs with non-X/Y-inputs cannot be XOR
 * @return A list of output wires that do not behave appropriately for this rule.
 */
vector<string> Day24Solution::assessRule2()
{
    vector<string> badOutputWires;
    for (const auto &gate : gates)
    {
        if (gate.outputWire[0] != 'z' &&
            gate.inputWire1[0] != 'x' && gate.inputWire1[0] != 'y' &&
            gate.inputWire2[0] != 'x' && gate.inputWire2[0] != 'y' &&
            gate.gate == "XOR")
            badOutputWires.push_back(gate.outputWire);
    }

    return badOutputWires;
}


/**
 * Rule 3: For any XOR-gate with X- and Y-input (except the first gate), there exists an XOR-gate that uses its output as input.
 * @return A list of output wires that do not behave appropriately for this rule.
 */
vector<string> Day24Solution::assessRule3()
{
    vector<string> badOutputWires;
    for (const auto &gate : gates)
    {
        if ((gate.inputWire1 == "x00" || gate.inputWire1 == "y00") && (gate.inputWire2 == "x00" || gate.inputWire2 == "y00"))
            continue;

        if (gate.gate == "XOR" &&
            (gate.inputWire1[0] == 'x' || gate.inputWire1[0] == 'y') &&
            (gate.inputWire2[0] == 'x' || gate.inputWire2[0] == 'y'))
        {
            bool downstreamXorFound {false};
            for (const auto &gate2 : gates)
            {
                if (gate2.gate == "XOR" && (gate2.inputWire1 == gate.outputWire || gate2.inputWire2 == gate.outputWire))
                {
                    downstreamXorFound = true;
                }
            }
            if (!downstreamXorFound)
                badOutputWires.push_back(gate.outputWire);
        }
    }
    return badOutputWires;
}


/**
 * For any AND-gate, there must be an OR-gate with its output as an input.
 * @return A list of output wires that do not behave appropriately for this rule.
 */
vector<string> Day24Solution::assessRule4()
{
    vector<string> badOutputWires;
    for (const auto &gate : gates)
    {
        if ((gate.inputWire1 == "x00" || gate.inputWire1 == "y00") && (gate.inputWire2 == "x00" || gate.inputWire2 == "y00"))
            continue;

        if (gate.gate == "AND")
        {
            bool upstreamGateFound {false};
            for (const auto &gate2 : gates)
            {
                if (gate2.gate == "OR" && (gate.outputWire == gate2.inputWire1  || gate.outputWire ==  gate2.inputWire2))
                {
                    upstreamGateFound = true;
                }
            }
            if (!upstreamGateFound)
                badOutputWires.push_back(gate.outputWire);
        }
    }
    return badOutputWires;
}


string Day24Solution::twoStarSolution()
{
    std::set<string> badOutputWires;

    for (const auto &ruleViolator : assessRule1())
        badOutputWires.insert(ruleViolator);

    for (const auto &ruleViolator : assessRule2())
        badOutputWires.insert(ruleViolator);

    for (const auto &ruleViolator : assessRule3())
        badOutputWires.insert(ruleViolator);

    for (const auto &ruleViolator : assessRule4())
        badOutputWires.insert(ruleViolator);

    string badWires;
    for ( const auto &wire : badOutputWires)
        badWires += wire + ",";

    return badWires.substr(0,badWires.length()-1);
}
