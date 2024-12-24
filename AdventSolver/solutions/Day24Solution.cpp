/** Dev: Dave West
 * Date: December 24, 2024
 * Desc: Method definitions for the AoC 2024 day Christmas Eve puzzle.
 */

#include "Day24Solution.h"

#include <sstream>
#include <cmath>

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
    while (!gates.empty())
    {
        auto end = gates.end();
        for (auto gate = gates.begin(); gate != end; ++gate)  //  Iterate through gates, we'll need the iterator to delete executed gates later
        {
            if (!inputWires.contains(gate->inputWire1))
                continue;
            if (!inputWires.contains(gate->inputWire2))
                continue;

            inputWires[gate->outputWire] = runGate(*gate);

            gates.erase(gate);
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



string Day24Solution::twoStarSolution()
{
    int result {0};

    return std::to_string(result);
}
