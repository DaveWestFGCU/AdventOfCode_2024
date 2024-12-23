/** Dev: Dave West
 * Date: December 23, 2024
 * Desc: Method definitions for the AoC 2024 day 23 puzzle.
 */

#include "Day23Solution.h"
#include <sstream>

Day23Solution::Day23Solution(const vector<string> &puzzleInput)
    : title("--- Day 23: LAN Party ---")
{
    parseLanConnections(puzzleInput);
}


void Day23Solution::parseLanConnections(const vector<string> &puzzleInput)
{
    for (const auto &connection : puzzleInput)
    {
        auto computers = split(connection, '-');

        // Add each computer in the connection to each other's connections
        if (!lanConnections.contains(computers[1]))
            lanConnections[computers[1]];

        lanConnections[computers[0]].connections[computers[1]] = &lanConnections[computers[1]];
        lanConnections[computers[1]].connections[computers[0]] = &lanConnections[computers[0]];
    }
}


vector<string> Day23Solution::split(const string &stringToParse, const char &delimiter)
{
    std::stringstream ss(stringToParse);
    string token;

    vector<string> tokens;
    while (std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}


string Day23Solution::oneStarSolution()
{
    findConnectionTriplets();

    int countNetworksWithTComputer {0};

    for(const auto &[first,second,third] : connectionTriplets)
    {
        // Looking for connections where the first letter of any computer is 't'
        if (first[0] == 't' || second[0] == 't' || third[0] == 't')
            ++countNetworksWithTComputer;
    }

    return std::to_string(countNetworksWithTComputer);
}


void Day23Solution::findConnectionTriplets()
{
    // Go 3 deep and see if the first computer exists in the third computer's connections.
    for (const auto &computer : lanConnections)
        for (const auto &firstConnection : computer.second.connections)
            for (const auto &secondConnection : firstConnection.second->connections)
                //  This much nesting makes me feel gross.

                if (secondConnection.second->connections.contains(computer.first))
                {
                    // Sort alphabetically and insert into set of tuples (to remove duplicate connection triplets).
                    string first = std::min(std::min(computer.first, firstConnection.first), secondConnection.first);
                    string second;
                    string third = std::max(std::max(computer.first, firstConnection.first), secondConnection.first);

                    if (first != computer.first && third != computer.first)
                        second = computer.first;
                    else if (first != firstConnection.first && third != firstConnection.first)
                        second = firstConnection.first;
                    else
                        second = secondConnection.first;

                    connectionTriplets.insert({first, second, third});
                }
}


string Day23Solution::twoStarSolution()
{
    int result { 0 };
    return std::to_string(result);
}
