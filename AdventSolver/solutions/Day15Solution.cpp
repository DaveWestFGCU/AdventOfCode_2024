/*  Dev: Dave West
 * Date: December 15, 2024
 * Desc: Method definitions for the AoC 2024 day 15 puzzle.
 */

#include "Day15Solution.h"


Day15Solution::Day15Solution(const vector<string> &puzzleInput)
    : title("--- Day 15: Warehouse Woes ---"), robot(-1,-1)
{
    parseInput(puzzleInput);
}


void Day15Solution::parseInput(const vector<string> &puzzleInput)
{
    bool parsingWarehouseMap = true;
    for (const auto &line : puzzleInput)
    {
        if (line.empty())
        {
            parsingWarehouseMap = false;
            continue;
        }

        if (parsingWarehouseMap)
            initialWarehouseState.push_back(line);

        if (!parsingWarehouseMap)
            moveInstructions += line;
    }
}


void Day15Solution::setRobotInitialPosition()
{
    for (int y = 0; y < warehouseMap.size(); ++y)
        for(int x = 0; x < warehouseMap[y].length(); ++x)
        {
            if (warehouseMap[y][x] == '@')
            {
                robot.x = x;
                robot.y = y;
                warehouseMap[y][x] = EMPTY_SPACE;  // We'll keep track of the robot outside the map and display the position when necessary.
                return;
            }
        }
}


void Day15Solution::printWarehouseState(vector<string> map) const
{
    // Check if robot has been initialized
    if (robot != Position(-1,-1))
    {
        // Render the robot
        map[robot.y][robot.x] = ROBOT;
    }

    // Print the map w/ robot to console
    for (const auto &line : map)
    {
        for (const auto &character : line)
            std::cout << character << " ";
        std::cout << std::endl;
    }
}


long long Day15Solution::oneStarSolution()
{
    warehouseMap = initialWarehouseState;
    setRobotInitialPosition();
    runMovementInstructions();

    int boxGPSCoordinateSum {0};
    vector<Position> boxes = findBoxes();
    for (const auto &box : boxes)
        boxGPSCoordinateSum += box.x + box.y*100;
    return boxGPSCoordinateSum;
}


void Day15Solution::runMovementInstructions()
{
    for (const auto &step : moveInstructions)
    {
        switch(step)
        {
            case NORTH:
                move(robot, {robot.x, robot.y-1}, NORTH);
                break;

            case EAST:
                move(robot, {robot.x+1, robot.y}, EAST);
                break;

            case SOUTH:
                move(robot, {robot.x, robot.y+1}, SOUTH);
                break;

            case WEST:
                move(robot, {robot.x-1, robot.y}, WEST);
                break;

            default:
                std::cerr << "Unknown instruction: ";
                std::cout << step << std::endl;
        }

        printWarehouseState(warehouseMap);
        string pause;
        std::cin >> pause;
    }
}


bool Day15Solution::move(const Position &object, const Position &nextPosition, const Direction &direction)
{
    if(isBlocked(nextPosition))
        return false;

    if(isClear(nextPosition))
    {
        moveObject(object, nextPosition);
        return true;
    }


    if (warehouseMap[nextPosition.y][nextPosition.x] == BOX || direction == EAST || direction == WEST)
        if (move(nextPosition, object + nextPosition, direction))
        {
            moveObject(object, nextPosition);
            return true;
        }

    if (warehouseMap[nextPosition.y][nextPosition.x] == BOX_LEFT)
    {
        Position rightPosition(object.x+1, object.y);
        Position nextRightPosition(nextPosition.x+1,nextPosition.y);

        if (move(nextPosition, object + nextPosition, direction) && move(nextRightPosition, rightPosition + nextRightPosition, direction))
        {
            moveObject(object, nextPosition);
            moveObject(rightPosition, nextRightPosition);
            return true;
        }
    }

    if (warehouseMap[nextPosition.y][nextPosition.x] == BOX_RIGHT)
    {
        Position leftPosition(object.x-1, object.y);
        Position nextLeftPosition(nextPosition.x-1, nextPosition.y);

        if (move(nextPosition, object + nextPosition, direction) && move(nextLeftPosition, leftPosition + nextLeftPosition, direction))
        {
            moveObject(object, nextPosition);
            moveObject(leftPosition, nextLeftPosition);
            return true;
        }
    }

    return false;
}


bool Day15Solution::isBlocked(const Position &pos) const
{
    return warehouseMap[pos.y][pos.x] == WALL;
}


bool Day15Solution::isClear(const Position &pos) const
{
    return warehouseMap[pos.y][pos.x] == EMPTY_SPACE;
}


void Day15Solution::moveObject(const Position &object, const Position &nextPosition)
{
    if (object == robot)
    {
        robot.x = nextPosition.x;
        robot.y = nextPosition.y;
    }
    else
    {
        warehouseMap[nextPosition.y][nextPosition.x] = warehouseMap[object.y][object.x];
        warehouseMap[object.y][object.x] = EMPTY_SPACE;
    }
}


vector<Day15Solution::Position> Day15Solution::findBoxes() const
{
    vector<Position> boxes;

    for (int y = 0; y < warehouseMap.size(); ++y)
        for (int x = 0; x < warehouseMap.size(); ++x)
            if (warehouseMap[y][x] == BOX || warehouseMap[y][x] == BOX_LEFT)
                boxes.emplace_back(x, y);

    return boxes;
}


long long Day15Solution::twoStarSolution()
{
    warehouseMap = doubleMapWidth(initialWarehouseState);
    setRobotInitialPosition();
    printWarehouseState(warehouseMap);

    runMovementInstructions();

    int boxGPSCoordinateSum {0};
    vector<Position> boxes = findBoxes();
    for (const auto &box : boxes)
        boxGPSCoordinateSum += box.x + box.y*100;
    return boxGPSCoordinateSum;
}


vector<string> Day15Solution::doubleMapWidth(const vector<string> &map) const
{
    vector<string> newMap;

    for (int y = 0; y < map.size(); ++y)
    {
        string newLine;
        for (int x = 0; x < map[y].length(); ++x)
        {
            switch(map[y][x])
            {
                case ROBOT:
                    newLine += ROBOT;
                    newLine += EMPTY_SPACE;
                    break;

                case BOX:
                    newLine += BOX_LEFT;
                    newLine += BOX_RIGHT;
                    break;

                default:
                    newLine += map[y][x];
                    newLine += map[y][x];
            }
        }
        newMap.push_back(newLine);
    }

    return newMap;
}


