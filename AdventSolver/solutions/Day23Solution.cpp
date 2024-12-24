/** Dev: Dave West
 * Date: December 23, 2024
 * Desc: Method definitions for the AoC 2024 day 23 puzzle.
 */

#include "Day23Solution.h"
#include <sstream>
#include <algorithm>

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
    auto maximalClique = findMaximalClique();
    std::ranges::sort(maximalClique);

    string password;
    for (const auto &computer : maximalClique)
        password += computer + ",";

    password = password.substr(0,password.length()-1);  //  Remove last comma

    return password;
}


vector<string> Day23Solution::findMaximalClique()
{
    vector<string> maximalClique;
    for (const auto &computer : lanConnections)
    {
        vector<string> currentClique;
        currentClique = _findMaximalClique(currentClique, computer.first);
        if (currentClique.size() > maximalClique.size())
            maximalClique = currentClique;
    }

    return maximalClique;
}


vector<string> Day23Solution::_findMaximalClique(vector<string> clique, const string &nextComputer)
{
    //  If any element in the current clique does not exist in the next computer's connections, don't add it to the clique.
    for (const auto &cliqueComputer : clique)
        if (!lanConnections[nextComputer].connections.contains(cliqueComputer))
            return clique;

    //  All clique nodes connect to next node: graph is still complete.
    clique.push_back(nextComputer);

    //  Get any new connections not already in the clique
    vector<string> newComputers;
    for (const auto &newComputer : lanConnections[nextComputer].connections)
    {
        if (std::find(clique.begin(), clique.end(), newComputer.first) == clique.end())
            newComputers.push_back(newComputer.first);
    }

    // Check new connections for larger cliques
    for (const auto &newComputer : newComputers)
    {
        vector<string> newClique = _findMaximalClique(clique, newComputer);
        if (newClique.size() > clique.size())
            clique = newClique;
    }

    // Return largest sub-clique
    return clique;
}
