

#include "Day6Solution.h"


Day6Solution::Day6Solution(const std::vector<std::string> & puzzleInput) : puzzleInput(puzzleInput), guardBob(Guard(puzzleInput))
{
    title = "--- Day 6: Guard Gallivant ---";
}


Day6Solution::Guard::Guard(const vector<string>& puzzleInput) : roomMap(puzzleInput)
{
    setGuardLocation();
    buildVisitedMap();
    status = PATROLING;
}


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


void Day6Solution::Guard::buildVisitedMap()
{
    vector<vector<Visited>> newVisitedMap;
    for (const auto &line : roomMap)
    {
        vector<Visited> visitedArrayLine;
        for (auto character : line)
        {
            visitedArrayLine.push_back(Visited{false, {false}});
        }
        newVisitedMap.push_back(visitedArrayLine);
    }

    newVisitedMap[location.y][location.x].atLeastOnce = true;
    newVisitedMap[location.y][location.x].facingList[facing] = true;

    visitedMap = newVisitedMap;
}


void Day6Solution::Guard::printMap()
{
    char facingChar;
    switch(facing)
    {
        case NORTH:
            facingChar = '^';
            break;
        case EAST:
            facingChar = '>';
            break;
        case SOUTH:
            facingChar = 'v';
            break;
        case WEST:
            facingChar = '<';

        default:
            facingChar = '?';
    }

    //for (const auto &row : visitedMap)
    //{
    //    for (const auto &[atLeastOnce, facingList] : row)
    //    {
    //        std::cout << (atLeastOnce ? facingChar : '.');
    //    }
    //    std::cout << std::endl;
    //}
}


/**
 * One step in the guard's patrol pathing.
 * @return Returns true if a cycle has not yet been found.
 */
void Day6Solution::Guard::patrol(vector<string> patrolMap)
{
    //std::cout << std::endl << "patrolMap" << std::endl;
    //for (auto line : patrolMap)
    //{
    //    for (auto item : line)
    //        std::cout << item;
    //    std::cout << std::endl;
    //}

    switch (facing)
    {
        case NORTH:
            if (isBlocked(patrolMap))
                facing = EAST;
            else
                location.y--;
            break;

        case EAST:
            if (isBlocked(patrolMap))
                facing = SOUTH;
            else
                location.x++;
            break;

        case SOUTH:
            if (isBlocked(patrolMap))
                facing = WEST;
            else
                location.y++;
            break;

        case WEST:
            if (isBlocked(patrolMap))
                facing = NORTH;
            else
                location.x--;
            break;
    }

    //std::cout << std::endl << "visitedMap" << std::endl;
    for (auto row : visitedMap)
    {
        for (auto item : row)
        {
            char guardDir = '?';
            switch(facing)
            {
                case NORTH:
                    guardDir = '^';
                    break;
                case EAST:
                    guardDir = '>';
                    break;
                case SOUTH:
                    guardDir = 'v';
                    break;
                case WEST:
                    guardDir = '<';
                    break;
            }
        //    std::cout << (item.atLeastOnce?guardDir:'.');
        }
        //std::cout << std::endl;
    }

    if (location.y < 0 || location.y >= patrolMap.size())
    {
        status = LEFT_AREA;
        return;
    }
    if (location.x < 0 || location.x >= patrolMap[0].length())
    {
        status = LEFT_AREA;
        return;
    }
    if (foundCycle())
    {
        status = LOOPING;
        return;
    }

    visitedMap[location.y][location.x].atLeastOnce = true;
    visitedMap[location.y][location.x].facingList[facing] = true;
}


bool Day6Solution::Guard::isBlocked(vector<string> patrolMap)
{
    switch (facing)
    {
        case NORTH:
            if (location.y-1 < 0)
                return false;

            if (patrolMap[location.y-1][location.x] == '#')
                return true;
            if (patrolMap[location.y-1][location.x] == 'O')
                return true;
        break;

        case EAST:
            if (location.x+1 >= patrolMap[0].length())
                return false;
            if (patrolMap[location.y][location.x+1] == '#')
                return true;
            if (patrolMap[location.y][location.x+1] == 'O')
                return true;
        break;

        case SOUTH:
            if (location.y+1 >= patrolMap[0].size())
                return false;
            if (patrolMap[location.y+1][location.x] == '#')
                return true;
            if (patrolMap[location.y+1][location.x] == 'O')
                return true;
        break;

        case WEST:
            if (location.x-1 < 0)
                return false;
            if (patrolMap[location.y][location.x-1] == '#')
                return true;
            if (patrolMap[location.y][location.x-1] == 'O')
                return true;
        break;
        }

    return false;
}


bool Day6Solution::Guard::foundCycle()
{
    if (visitedMap[location.y][location.x].atLeastOnce)
        if (visitedMap[location.y][location.x].facingList[facing])
            return true;

    return false;
}


int Day6Solution::oneStarSolution()
{
        // Loop until Bob's status changes to LEFT_AREA
    while(guardBob.getStatus() == Guard::PATROLING)
        guardBob.patrol();

    return static_cast<int>(countVisitedLocations());
}



size_t Day6Solution::countVisitedLocations()
{
    return guardBob.countVisitedLocations();
}


size_t Day6Solution::Guard::countVisitedLocations()
{
    size_t visitedLocationCount {0};
    for (auto row : visitedMap)
        for (auto visited : row)
            if (visited.atLeastOnce)
                visitedLocationCount++;

    return visitedLocationCount;
}


int Day6Solution::twoStarSolution()
{
    return static_cast<int>(bruteForcedTwoStar());
}


void Day6Solution::Guard::reset()
{
    setGuardLocation();
    buildVisitedMap();
    status = PATROLING;
}


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

                std::cout << "[" << row << "][" << col << "] : " << guardBob.getStatus() << std::endl;

                if (guardBob.getStatus() == Guard::LOOPING)
                    loopCount++;
            }
        }
    }

    return loopCount;
}