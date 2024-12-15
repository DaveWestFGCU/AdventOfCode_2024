/*  Dev: Dave West
 * Date: December 15, 2024
 * Desc: Method definitions for the AoC 2024 day 15 puzzle.
 */

#include "Day15Solution.h"


Day15Solution::Day15Solution(const vector<string> &puzzleInput)
    : title("--- Day 15: Warehouse Woes ---")
{
    parseInput(puzzleInput);
    setRobotInitialPosition();
}


void Day15Solution::parseInput(const vector<string> &puzzleInput)
{
    bool parsingWarehouseMap = true;
    for (auto line : puzzleInput)
    {
        if (line == "")
        {
            parsingWarehouseMap = false;
            continue;
        }

        if (parsingWarehouseMap)
            warehouseMap.push_back(line);

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
                warehouseMap[y][x] = '.';  // We'll keep track of the robot outside of the map and display the position when necessary.
                return;
            }
        }
}


void Day15Solution::printWarehouseState()
{
    // Render the robot
    vector tempMap(warehouseMap);
    tempMap[robot.y][robot.x] = '@';

    // Print the map w/ robot to console
    for (auto line : tempMap)
        std::cout << line << std::endl;
    std::cout << std::endl;
}


long long Day15Solution::oneStarSolution()
{
    runMovementInstructions();

    int boxGPSCoordinateSum {0};
    vector<Position> boxes = findBoxes();
    for (auto box : boxes)
        boxGPSCoordinateSum += box.x + box.y*100;
    return boxGPSCoordinateSum;
}


void Day15Solution::runMovementInstructions()
{
    for (auto step : moveInstructions)
    {
        switch(step)
        {
            case '^':
                move(robot, {robot.x, robot.y-1});
                break;

            case '>':
                move(robot, {robot.x+1, robot.y});
                break;

            case 'v':
                move(robot, {robot.x, robot.y+1});
                break;

            case '<':
                move(robot, {robot.x-1, robot.y});
                break;

            default:
                std::cerr << "Unknown instruction: ";
                std::cout << step << std::endl;
        }
    }
}


bool Day15Solution::move(const Position object, const Position nextPosition)
{
    if(isBlocked(nextPosition))
        return false;

    if(isClear(nextPosition))
    {
        moveObject(object, nextPosition);
        return true;
    }

    // Not blocked, not clear = must be a box. Check if its blocked or clear.
    if(move(nextPosition, object + nextPosition))
    {
        moveObject(object, nextPosition);
        return true;
    }

    return false;
}


bool Day15Solution::isBlocked(const Position &pos)
{
    return warehouseMap[pos.y][pos.x] == '#';
}


bool Day15Solution::isClear(const Position &pos)
{
    return warehouseMap[pos.y][pos.x] == '.';
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
        warehouseMap[nextPosition.y][nextPosition.x] = 'O';
        warehouseMap[object.y][object.x] = '.';
    }
}


vector<Day15Solution::Position> Day15Solution::findBoxes() const
{
    vector<Position> boxes;

    for (int y = 0; y < warehouseMap.size(); ++y)
        for (int x = 0; x < warehouseMap.size(); ++x)
            if (warehouseMap[y][x] == 'O')
                boxes.emplace_back(x, y);

    return boxes;
}


long long Day15Solution::twoStarSolution()
{
    int result {0};

    return result;
}
