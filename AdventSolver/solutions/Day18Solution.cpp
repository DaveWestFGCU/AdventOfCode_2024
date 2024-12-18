/** Dev: Dave West
 * Date: December 18, 2024
 * Desc: Method definitions for the AoC 2024 day 18 puzzle.
 */

#include "Day18Solution.h"


Day18Solution::Day18Solution(const vector<string> &puzzleInput)
    : title("--- Day 18: RAM Run ---")
{
    parseCorruptedMemory(puzzleInput);

    if (corruptedMemoryLocations.size() == 25)
    {   xBounds = 7; yBounds = 7; fallenMemoryCount = 12;   }
    else
    {   xBounds = 71; yBounds = 71; fallenMemoryCount = 1024;   }

    buildMemoryMap();
    printMemoryMap();
}


void Day18Solution::parseCorruptedMemory(const vector<string> &puzzleInput)
{
    for (const auto &line : puzzleInput)
    {
        bool passedComma {false};
        int first {0}, second {0};
        for (const char &character : line)
        {
            if (character == ',')
            {
                passedComma = true;
                continue;
            }

            if (!passedComma)
                first = first * 10 + (character - '0');
            else
                second = second * 10 + (character -'0');
        }
        corruptedMemoryLocations.emplace_back(first,second);
    }
}


void Day18Solution::printCorruptedMemory()
{
    for (const auto &[x, y] : corruptedMemoryLocations)
        std::cout << "( " << x << ", " << y << " )" << std::endl;
}


void Day18Solution::buildMemoryMap()
{
    for (int y = 0; y < yBounds; ++y)
    {
        vector<MemoryLoc> line;
        for (int x = 0; x < xBounds; ++x)
            line.emplace_back(x, y, '.');
        memoryMap.push_back(line);
    }

    for (int fallenMemory = 0; fallenMemory < fallenMemoryCount; ++fallenMemory)
    {
        auto [x, y] = corruptedMemoryLocations[fallenMemory];
        memoryMap[x][y].value = '#';
        memoryMap[x][y].safe = false;
    }

    for (int y = 0; y < yBounds; ++y)
        for (int x = 0; x < xBounds; ++x)
        {
            MemoryLoc *currentLoc = &memoryMap[x][y];
            if (y > 0)
                currentLoc->neighbor[NORTH] = &memoryMap[x][y-1];
            if (x < xBounds-1)
                currentLoc->neighbor[EAST] = &memoryMap[x+1][y];
            if (y < yBounds-1)
                currentLoc->neighbor[SOUTH] = &memoryMap[x][y+1];
            if (x > 0)
                currentLoc->neighbor[WEST] = &memoryMap[x-1][y];
        }
}


void Day18Solution::printMemoryMap()
{
    for (const auto &line : memoryMap)
    {
        for (const auto &loc : line)
            std::cout << loc.value;
        std::cout << std::endl;
    }
}


string Day18Solution::oneStarSolution()
{
    return std::to_string(findShortestPath(xBounds-1, yBounds-1));
}


int Day18Solution::findShortestPath(int searchX, int searchY)
{
    int numSteps {0};
    std::queue<MemoryLoc *> unvisited;
    unvisited.push(&memoryMap[0][0]);
    memoryMap[0][0].queued = true;

    while (!unvisited.empty())
    {
        std::queue<MemoryLoc *> unvisitedStep(unvisited);
        while(!unvisited.empty())
            unvisited.pop();

        while (!unvisitedStep.empty())
        {
            MemoryLoc *visiting = unvisitedStep.front();

            if (visiting->x == searchX && visiting->y == searchY)
                return numSteps;    //  End found

            visiting->visited = true;
            visiting->value = 'O';

            // Add neighbors to queue if exists, has not been queued, and is safe
            for (int direction = NORTH; direction <= WEST; direction++)
            {
                if (visiting->neighbor[direction])
                {
                    if (!visiting->neighbor[direction]->queued && visiting->neighbor[direction]->safe)
                    {
                        unvisited.push(visiting->neighbor[direction]);
                        visiting->neighbor[direction]->queued = true;
                    }
                }
            }   // Added any unvisited neighbors to next visiting wave

            unvisitedStep.pop();
        }   //  All tiles in step visited

        ++numSteps;
    }   //  No reachable tiles remaining

    return -1;  // Unable to reach desired location
}


string Day18Solution::twoStarSolution()
{
    int result {0};

    return std::to_string(result);
}
