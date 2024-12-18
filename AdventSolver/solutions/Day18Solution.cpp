/** Dev: Dave West
 * Date: December 18, 2024
 * Desc: Method definitions for the AoC 2024 day 18 puzzle.
 */

#include "Day18Solution.h"

#include <cmath>


Day18Solution::Day18Solution(const vector<string> &puzzleInput)
    : title("--- Day 18: RAM Run ---")
{
    parseCorruptedMemory(puzzleInput);

    int fallenMemoryTotal;
    if (corruptedMemoryLocations.size() == 25)
    {   xBounds = 7; yBounds = 7; fallenMemoryTotal = 12;   }
    else
    {   xBounds = 71; yBounds = 71; fallenMemoryTotal = 1024;   }

    buildMemoryMap(fallenMemoryTotal);
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


void Day18Solution::buildMemoryMap(const int &fallenMemoryTotal)
{
    memoryMap.clear();

    for (int y = 0; y < yBounds; ++y)
    {
        vector<MemoryLoc> line;
        for (int x = 0; x < xBounds; ++x)
            line.emplace_back(x, y, '.');
        memoryMap.push_back(line);
    }

    for (int fallenMemoryCount = 0; fallenMemoryCount < fallenMemoryTotal; ++fallenMemoryCount)
    {
        auto [x, y] = corruptedMemoryLocations[fallenMemoryCount];
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
    int shortestPathLength = findShortestPath(xBounds-1, yBounds-1);

    return std::to_string(shortestPathLength);
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
    // Array for some memoization on the upcoming binary search for the interrupting corruption index.
    int shortestPathLengths[corruptedMemoryLocations.size()];
    for (int i = 0; i < corruptedMemoryLocations.size(); ++i)
        shortestPathLengths[i] = 0;

    int firstIndex = findFirstPathInterruption(0, corruptedMemoryLocations.size()-1, shortestPathLengths);
    auto [x, y] = corruptedMemoryLocations[firstIndex];

    return std::to_string(x) + "," + std::to_string(y);
}


/**
 * Binary search, testing maps as corruption is added and using memoization to prevent re-testing.
 * @param leftIndex
 * @param rightIndex
 * @param shortestPathLengths
 * @return
 */
int Day18Solution::findFirstPathInterruption(const int leftIndex, const int rightIndex, int shortestPathLengths[])
{
    int midIndex = std::floor((leftIndex + rightIndex) /2);

    int midPathLength;
    if (shortestPathLengths[midIndex])
        midPathLength = shortestPathLengths[midIndex];
    else
    {
        buildMemoryMap(midIndex);
        midPathLength = findShortestPath(xBounds-1, yBounds-1);
        shortestPathLengths[midIndex] = midPathLength;
    }

    int prevPathLength;
    if (shortestPathLengths[midIndex-1])
        prevPathLength = shortestPathLengths[midIndex-1];
    else
    {
        buildMemoryMap(midIndex);
        prevPathLength = findShortestPath(xBounds-1, yBounds-1);
        shortestPathLengths[midIndex-1] = prevPathLength;
    }

    if (prevPathLength > 0 && midPathLength < 0)
        return midIndex;

    if (midPathLength > 0)  // Path exists
        return findFirstPathInterruption(midIndex+1, rightIndex, shortestPathLengths);

    //  No path exists
    return findFirstPathInterruption(leftIndex, midIndex, shortestPathLengths);
}
