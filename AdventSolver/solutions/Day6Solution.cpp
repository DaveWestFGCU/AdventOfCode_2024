/**  Dev: Dave West
 * Date: December 6, 2024
 * Desc: Method definitions for the AoC 2024 day 6 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#include "Day6Solution.h"

/**
 * Day6Solution Constructor.
 * @param puzzleInput Day 6 puzzle input from AdventOfCode.com.
 */
Day6Solution::Day6Solution(const std::vector<std::string> & puzzleInput) : puzzleInput(puzzleInput), guardBob(Guard(puzzleInput))
{
    title = "--- Day 6: Guard Gallivant ---";
}


/**
 * Guard constructor.
 * @param puzzleInput Day 6 puzzle input from AdventOfCode.com.
 */
Day6Solution::Guard::Guard(const vector<string>& puzzleInput) : roomMap(puzzleInput)
{
    setGuardLocation();
    buildVisitedMap();
    status = PATROLING;
}


/**
 * Finds the guard in the puzzle and sets the location and direction he's facing.
 */
void Day6Solution::Guard::setGuardLocation()
{
    for (int row = 0; row < roomMap.size(); row++)
    {
        for (int col = 0; col < roomMap[0].length(); col++)
        {
            if (roomMap[row][col] != '.')
            {
                if (roomMap[row][col] == '^')
                {
                    location.y = row;
                    location.x = col;
                    facing = NORTH;
                }

                else if (roomMap[row][col] == 'v')
                {
                    location.x = row;
                    location.y = col;
                    facing = SOUTH;
                }

                else if (roomMap[row][col] == '>')
                {
                    location.x = row;
                    location.y = col;
                    facing = EAST;
                }

                else if (roomMap[row][col] == '<')
                {
                    location.x = row;
                    location.y = col;
                    facing = WEST;
                }
            }
        }
    }
}


/**
 * Makes a new, blank visited map.
 */
void Day6Solution::Guard::buildVisitedMap()
{
    vector<vector<bool>> newVisitedMap;
    for (const auto &line : roomMap)
    {
        vector<bool> visitedLine;
        for (int i = 0; i < line.size(); i++)
        {
            visitedLine.push_back(false);
        }
        newVisitedMap.push_back(visitedLine);
    }

    visitedMap = newVisitedMap;
}


/**
 * Prints the puzzle map with 'X' on tiles the guard has visited.
 * @param patrolMap
 */
void Day6Solution::Guard::printMap(const vector<string> & patrolMap)
{
    vector mergedMap(patrolMap);

    for (size_t y = 0; y < visitedMap.size(); y++)
    {
        for (size_t x = 0; x < visitedMap[0].size(); x++)
            if (visitedMap[y][x])
                mergedMap[y][x] = 'X';
    }

    if (location.y >= 0 && location.y < patrolMap.size()
        && location.x >= 0 && location.x < patrolMap[0].length())
    {
        switch(facing)
        {
            case NORTH:
                mergedMap[location.y][location.x] = '^';
            break;

            case EAST:
                mergedMap[location.y][location.x] = '>';
            break;

            case SOUTH:
                mergedMap[location.y][location.x] = 'v';
            break;

            case WEST:
                mergedMap[location.y][location.x] = '<';
            break;
        }
    }

    std::cout << std::endl;
    for (const auto &row : mergedMap)
    {
        for (const auto &item : row)
        {
            std::cout << item;
        }
        std::cout << std::endl;
    }
}


/**
 * The guard turns 90deg clockwise until unblocked and walks until blocked again.
 * @return Returns the guard's status. If still patroling, run again.
 */
Day6Solution::Guard::GuardStatus Day6Solution::Guard::patrol(const vector<string>& patrolMap)
{
    while (isBlocked(patrolMap))
    {
        if (inLoop())
        {
            return status;
        }
        turn();
    }

    while(!isOutOfBounds(patrolMap) && !isBlocked(patrolMap))
    {
        move();
    }

    if (isOutOfBounds(patrolMap))
    {
        return status;
    }

    return status;
}


/**
 * Turns direction of 'facing' 90deg clockwise.
 */
void Day6Solution::Guard::turn()
{
    switch (facing)
    {
        case NORTH:
            facing = EAST;
            break;

        case EAST:
            facing = SOUTH;
            break;

        case SOUTH:
            facing = WEST;
            break;

        case WEST:
            facing = NORTH;
            break;
    }
}   // end turn


/**
 * Moves the guard one space 'forward', depending on direction facing.
 */
void Day6Solution::Guard::move()
{
    visitedMap[location.y][location.x] = true;

    switch (facing)
    {
        case NORTH:
            location.y--;
            break;

        case EAST:
            location.x++;
            break;

        case SOUTH:
            location.y++;
            break;

        case WEST:
            location.x--;
            break;
    }
}


/**
 * Checks if there is an obstruction in front of the guard, based on direction facing.
 * @param patrolMap Map of the room.
 * @return True if there is an obstruction in front of the guard.
 */
bool Day6Solution::Guard::isBlocked(const vector<string> & patrolMap)
{
    switch (facing)
    {
        case NORTH:
            if (location.y-1 < 0)
                return false;
            if (patrolMap[location.y-1][location.x] == '#' || patrolMap[location.y-1][location.x] == 'O')
                return true;
            break;

        case EAST:
            if (location.x+1 >= patrolMap[0].length())
                return false;
            if (patrolMap[location.y][location.x+1] == '#' || patrolMap[location.y][location.x+1] == 'O')
                return true;
            break;

        case SOUTH:
            if (location.y+1 >= patrolMap[0].size())
                return false;
            if (patrolMap[location.y+1][location.x] == '#' || patrolMap[location.y+1][location.x] == 'O')
                return true;
            break;

        case WEST:
            if (location.x-1 < 0)
                return false;
            if (patrolMap[location.y][location.x-1] == '#' || patrolMap[location.y][location.x-1] == 'O')
                return true;
            break;
        }

    return false;
}


/**
 * Checks if the guard is out of bounds.
 * @param patrolMap Map of the room.
 * @return True if guard is out of bounds.
 */
bool Day6Solution::Guard::isOutOfBounds(const vector<string>& patrolMap)
{
    if (location.y < 0 || patrolMap.size() <= location.y || location.x < 0 || patrolMap[0].length() <= location.x)
        status = LEFT_AREA;

    return status == LEFT_AREA;
}


/**
 * Solution to the puzzle's first gold star.
 * @return Returns answer to the one-star puzzle.
 */
string Day6Solution::oneStarSolution()
{
        // Loop until Bob's status changes to LEFT_AREA
    while(guardBob.getStatus() == Guard::PATROLING)
        guardBob.patrol();

    return std::to_string(countVisitedLocations());
}


/**
 * Passes forward the number of positions the guard has visited.
 * @return Returns the number of positions visited by the guard.
 */
size_t Day6Solution::countVisitedLocations()
{
    return guardBob.countVisitedLocations();
}


/**
 * Counts the number of positions the guard has visited.
 * @return Returns the number of positions visited by the guard.
 */
size_t Day6Solution::Guard::countVisitedLocations()
{
    size_t visitedLocationCount {0};
    for (const auto& row : visitedMap)
        for (const auto& visited : row)
            if (visited)
                visitedLocationCount++;

    return visitedLocationCount;
}


/**
 * Solution to the puzzle's second gold star.
 * @return Returns answer to the two-star puzzle.
 */
string Day6Solution::twoStarSolution()
{
    return std::to_string(optimizedTwoStar());
}


/**
 * Resets the guard to the starting position.
 */
void Day6Solution::Guard::reset()
{
    setGuardLocation();
    buildVisitedMap();
    seenObstructions.clear();
    status = PATROLING;
}


/**
 * Second star solution with a brute-force approach. Checks whether the addition of a new obstacle at every position
 * would result in a loop.
 * @return Returns number of positions of obstructions would cause a loop.
 */
size_t Day6Solution::bruteForcedTwoStar()
{
    int loopCount {0};
    for (int row = 0; row < puzzleInput.size(); row++)
    {
        for (int col = 0; col < puzzleInput[0].length(); col++)
        {
            if (puzzleInput[row][col] == '.')
            {
                // Add a new obstruction
                vector tempPuzzleInput(puzzleInput);
                tempPuzzleInput[row][col] = 'O';

                guardBob.reset();

                while(guardBob.getStatus() == Guard::PATROLING)
                    guardBob.patrol(tempPuzzleInput);

                if (guardBob.getStatus() == Guard::LOOPING)
                    loopCount++;
            }
        }
    }

    return loopCount;
}


/**
 * Checks whether the guard is currently in a loop.
 * @return True if guard has been in this position with this obstacle before.
 */
bool Day6Solution::Guard::inLoop()
{
    string obstructionLocation;
    switch(facing)
    {
        case NORTH:
            obstructionLocation = std::to_string(location.y-1) + ',' + std::to_string(location.x);
            if (seenObstructions.contains(obstructionLocation))
            {
                if (seenObstructions[obstructionLocation][NORTH])
                    status = LOOPING;
                else
                    seenObstructions[obstructionLocation][NORTH] = true;
            }
            else
                seenObstructions[obstructionLocation] = {true, false, false, false};
            break;

        case EAST:
            obstructionLocation = std::to_string(location.y) + ',' + std::to_string(location.x+1);
            if (seenObstructions.contains(obstructionLocation))
            {
                if (seenObstructions[obstructionLocation][EAST])
                    status = LOOPING;
                else
                    seenObstructions[obstructionLocation][EAST] = true;
            }
            else
                seenObstructions[obstructionLocation] = {false, true, false, false};
            break;

        case SOUTH:
            obstructionLocation = std::to_string(location.y+1) + ',' + std::to_string(location.x);
            if (seenObstructions.contains(obstructionLocation))
            {
                if (seenObstructions[obstructionLocation][SOUTH])
                    status = LOOPING;
                else
                    seenObstructions[obstructionLocation][SOUTH] = true;
            }
            else
                seenObstructions[obstructionLocation] = {false, false, true, false};
            break;

        case WEST:
            obstructionLocation = std::to_string(location.y) + ',' + std::to_string(location.x-1);
            if (seenObstructions.contains(obstructionLocation))
            {
                if (seenObstructions[obstructionLocation][WEST])
                    status = LOOPING;
                else
                    seenObstructions[obstructionLocation][WEST] = true;
            }
            else
                seenObstructions[obstructionLocation] = {false, false, false, true};
            break;
    }

    return status == LOOPING;
}


/**
 * Optimized solution for the second star problem.
 * Only checks whether positions the guard occupied in the first problem for new obstacles to cause loops.
 * @return Number of positions that result in a loop.
 */
size_t Day6Solution::optimizedTwoStar()
{
    int loopCount {0};
    vector visitedLocations {guardBob.getVisitedLocations()};

    for (auto [row, col] : visitedLocations)
    {
        // Add a new obstruction
        vector tempPuzzleInput(puzzleInput);
        tempPuzzleInput[row][col] = 'O';

        guardBob.reset();

        while(guardBob.getStatus() == Guard::PATROLING)
            guardBob.patrol(tempPuzzleInput);

        if (guardBob.getStatus() == Guard::LOOPING)
            loopCount++;
    }

    return loopCount;
}


/**
 * Gets the locations visited by the guard in the last problem.
 * @return Returns (y,x) pairs of locations visited.
 */
vector<std::pair<int,int>> Day6Solution::Guard::getVisitedLocations()
{
    vector<std::pair<int, int>> visitedLocations;

    for (int y = 0; y < visitedMap.size(); y++)
        for (int x = 0; x < visitedMap[0].size(); x++)
            if (visitedMap[y][x])
                visitedLocations.emplace_back(y,x);

    return visitedLocations;
}
