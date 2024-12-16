/** Dev: Dave West
 * Date: December 15, 2024
 * Desc: Method definitions for the AoC 2024 day 15 puzzle.
 **/

#include "Day15Solution.h"


Day15Solution::Day15Solution(const vector<string> &puzzleInput)
    : title("--- Day 15: Warehouse Woes ---"), robot(&warehouseMap)
{
    parseInput(puzzleInput);
    setRobotInitialPosition();
}


void Day15Solution::parseInput(const vector<string> &puzzleInput)
{
    bool parsingWarehouseMap = true;
    for (const auto &line : puzzleInput)
    {
        if (line.empty())   // Warehouse map and instructions are separated by an empty line
        {
            parsingWarehouseMap = false;
            continue;
        }

        if (parsingWarehouseMap)
            initialMap.push_back(line);

        if (!parsingWarehouseMap)
            for(auto instruction : line)
                moveInstructions.push_back(static_cast<Direction>(instruction));
    }
    warehouseMap = initialMap;
}


void Day15Solution::setRobotInitialPosition()
{
    for (int y = 0; y < warehouseMap.size(); ++y)
        for(int x = 0; x < warehouseMap[y].length(); ++x)
        {
            if (warehouseMap[y][x] == ROBOT)
            {
                robot.setPosition(x,y);
                warehouseMap[y][x] = SPACE;  // We'll keep track of the robot outside the map and display the position when necessary.
                return;
            }
        }
}


void Day15Solution::printWarehouseState() const
{
    // Render the robot
    vector tempMap(warehouseMap);
    tempMap[robot.getY()][robot.getX()] = ROBOT;

    // Print the map w/ robot to console
    for (const auto &line : tempMap)
        std::cout << line << std::endl;
    std::cout << std::endl;
}


long long Day15Solution::oneStarSolution()
{
    runMovementInstructions();

    int boxGPSCoordinateSum {0};

    for (const auto &[x, y] : findBoxes())
        boxGPSCoordinateSum += x + y*100;

    return boxGPSCoordinateSum;
}


void Day15Solution::runMovementInstructions()
{
    for (const auto instruction : moveInstructions)
        robot.move(instruction);
}


void Day15Solution::Robot::move(const Direction &direction)
{
    const Position nextPosition = getNextPosition(position, direction);

    if (isBlocked(nextPosition))
        return;

    if (isClear(nextPosition))
        setPosition(nextPosition);

    if (pushIsClear(nextPosition, direction))
    {
        pushBox(nextPosition, direction);
        setPosition(nextPosition);
    }
}


bool Day15Solution::Robot::isBlocked(const Position &pos) const
{
    return (*warehouseMap)[pos.y][pos.x] == WALL;
}


bool Day15Solution::Robot::isClear(const Position &pos) const
{
    return (*warehouseMap)[pos.y][pos.x] == SPACE;
}


bool Day15Solution::Robot::pushIsClear(const Position object, const Direction &direction)
{
    const Position nextPosition = getNextPosition(object, direction);
    const char currentTile = (*warehouseMap)[object.y][object.x];

    if (currentTile == BOX || direction == EAST || direction == WEST)
    {
        if (isBlocked(nextPosition))
            return false;

        if (isClear(nextPosition))
            return true;

        return pushIsClear(nextPosition, direction);
    }

    if (currentTile == BOX_LEFT && (direction == NORTH || direction == SOUTH))
    {
        const Position nextBoxRightPosition(nextPosition.x+1, nextPosition.y);

        if (isBlocked(nextPosition) || isBlocked(nextBoxRightPosition))
            return false;

        if (isClear(nextPosition) && isClear(nextBoxRightPosition))
            return true;

        if (isClear(nextPosition))
            return pushIsClear(nextBoxRightPosition, direction);

        if (isClear(nextBoxRightPosition))
            return pushIsClear(nextPosition, direction);

        if (pushIsClear(nextPosition, direction) && pushIsClear(nextBoxRightPosition, direction))
            return true;

        return false;
    }

    if (currentTile == BOX_RIGHT && (direction == NORTH || direction == SOUTH))
    {
        const Position nextBoxLeftPosition(nextPosition.x-1, nextPosition.y);

        if (isBlocked(nextPosition) || isBlocked(nextBoxLeftPosition))
            return false;

        if (isClear(nextPosition) && isClear(nextBoxLeftPosition))
            return true;

        if (isClear(nextPosition))
            return pushIsClear(nextBoxLeftPosition, direction);

        if (isClear(nextBoxLeftPosition))
            return pushIsClear(nextPosition, direction);

        if (pushIsClear(nextPosition, direction) && pushIsClear(nextBoxLeftPosition, direction))
            return true;

        return false;
    }

    return false;
}


void Day15Solution::Robot::pushBox(const Position object, const Direction &direction)
{
    const Position nextPosition = getNextPosition(object, direction);
    char currentTile = (*warehouseMap)[object.y][object.x];

    if (currentTile == BOX || direction == EAST || direction == WEST)
    {
        if (!isClear(nextPosition))
            pushBox(nextPosition, direction);

        (*warehouseMap)[nextPosition.y][nextPosition.x] = (*warehouseMap)[object.y][object.x];
        (*warehouseMap)[object.y][object.x] = SPACE;
        return;
    }

    if (currentTile == BOX_LEFT && (direction == NORTH || direction == SOUTH))
    {
        Position boxRight(object.x+1,object.y);
        Position nextBoxRightPosition(nextPosition.x+1, nextPosition.y);

        if (!isClear(nextPosition))
            pushBox(nextPosition, direction);

        if (!isClear(nextBoxRightPosition))
            pushBox(nextBoxRightPosition, direction);

        (*warehouseMap)[nextPosition.y][nextPosition.x] = BOX_LEFT;
        (*warehouseMap)[object.y][object.x] = SPACE;

        (*warehouseMap)[nextBoxRightPosition.y][nextBoxRightPosition.x] = BOX_RIGHT;
        (*warehouseMap)[boxRight.y][boxRight.x] = SPACE;
        return;
    }

    if (currentTile == BOX_RIGHT && (direction == NORTH || direction == SOUTH))
    {
        Position boxLeft(object.x-1,object.y);
        Position nextBoxLeftPosition(nextPosition.x-1, nextPosition.y);

        if (!isClear(nextPosition))
            pushBox(nextPosition, direction);

        if (!isClear(nextBoxLeftPosition))
            pushBox(nextBoxLeftPosition, direction);

        (*warehouseMap)[nextPosition.y][nextPosition.x] = BOX_RIGHT;
        (*warehouseMap)[object.y][object.x] = SPACE;

        (*warehouseMap)[nextBoxLeftPosition.y][nextBoxLeftPosition.x] = BOX_LEFT;
        (*warehouseMap)[boxLeft.y][boxLeft.x] = SPACE;
    }
}


Day15Solution::Position Day15Solution::Robot::getNextPosition(const Position &startPosition,const Direction &direction)
{
    switch (direction)
    {
        case NORTH:
            return {startPosition.x, startPosition.y-1};

        case EAST:
            return {startPosition.x+1, startPosition.y};

        case SOUTH:
            return {startPosition.x, startPosition.y+1};

        case WEST:
            return {startPosition.x-1, startPosition.y};
    }
}


vector<Day15Solution::Position> Day15Solution::findBoxes() const
{
    vector<Position> boxes;

    for (int y = 0; y < warehouseMap.size(); ++y)
        for (int x = 0; x < warehouseMap[y].length(); ++x)
            if (warehouseMap[y][x] == BOX || warehouseMap[y][x] == BOX_LEFT)
                boxes.emplace_back(x, y);

    return boxes;
}


long long Day15Solution::twoStarSolution()
{
    doubleWarehouseWidth();
    setRobotInitialPosition();

    runMovementInstructions();

    int boxGPSCoordinateSum {0};
    for (const auto &[x, y] : findBoxes())
        boxGPSCoordinateSum += x + y*100;

    return boxGPSCoordinateSum;
}


void Day15Solution::doubleWarehouseWidth()
{
    vector<string> newMap;
    for (int y = 0; y < initialMap.size(); ++y)
    {
        string newLine;
        for (int x = 0; x < initialMap[y].size(); ++x)
        {
            switch (initialMap[y][x])
            {
                case WALL:
                    newLine += static_cast<char>(WALL);
                    newLine += static_cast<char>(WALL);
                    break;

                case BOX:
                    newLine += static_cast<char>(BOX_LEFT);
                    newLine += static_cast<char>(BOX_RIGHT);
                    break;

                case SPACE:
                    newLine += static_cast<char>(SPACE);
                    newLine += static_cast<char>(SPACE);
                    break;

                case ROBOT:
                    newLine += static_cast<char>(ROBOT);
                    newLine += static_cast<char>(SPACE);
                    break;
            }
        }
        newMap.push_back(newLine);
    }
    warehouseMap = newMap;
}
