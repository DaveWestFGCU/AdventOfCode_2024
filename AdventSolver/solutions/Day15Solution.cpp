/** Dev: Dave West
 * Date: December 15, 2024
 * Desc: Method definitions for the AoC 2024 day 15 puzzle.
 **/

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
    for (const auto &line : puzzleInput)
    {
        if (line.empty())   // Warehouse map and instructions are separated by an empty line
        {
            parsingWarehouseMap = false;
            continue;
        }

        if (parsingWarehouseMap)
            warehouseMap.push_back(line);

        if (!parsingWarehouseMap)
            for(auto instruction : line)
                moveInstructions.push_back(static_cast<Direction>(instruction));
    }
}


void Day15Solution::setRobotInitialPosition()
{
    for (int y = 0; y < warehouseMap.size(); ++y)
        for(int x = 0; x < warehouseMap[y].length(); ++x)
        {
            if (warehouseMap[y][x] == ROBOT)
            {
                robot.x = x;
                robot.y = y;
                warehouseMap[y][x] = SPACE;  // We'll keep track of the robot outside the map and display the position when necessary.
                return;
            }
        }
}


void Day15Solution::printWarehouseState() const
{
    // Render the robot
    vector tempMap(warehouseMap);
    tempMap[robot.y][robot.x] = ROBOT;

    // Print the map w/ robot to console
    for (const auto &line : tempMap)
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
    for (const auto instruction : moveInstructions)
    {
        move(robot, instruction);

        // Set to true to view ste-by-step diagrams
        if constexpr (false)
        {
            printWarehouseState();
            string pause;
            std::cin >> pause;
        }
    }
}


bool Day15Solution::move(const Position object, const Direction &direction)
{
    const Position nextPosition = getNextPosition(object, direction);

    if(isBlocked(nextPosition))
        return false;

    if(isClear(nextPosition))
    {
        moveObject(object, nextPosition);
        return true;
    }

    // Not blocked, not clear = must be a box. Check if its blocked or clear.
    if (move(nextPosition, direction))
    {
        moveObject(object, nextPosition);
        return true;
    }

    return false;
}


Day15Solution::Position Day15Solution::getNextPosition(const Position &startPosition,const Direction &direction)
{
    switch(direction)
    {
        case NORTH:
            return {startPosition.x, startPosition.y-1};

        case EAST:
            return {startPosition.x+1, startPosition.y};

        case SOUTH:
            return {startPosition.x, startPosition.y+1};

        case WEST:
            return {startPosition.x-1, startPosition.y};

        default:
            std::cerr << "Unknown direction: ";
        std::cout << static_cast<char>(direction) << std::endl;
        return {-1, -1};
    }
}


bool Day15Solution::isBlocked(const Position &pos) const
{
    return warehouseMap[pos.y][pos.x] == WALL;
}


bool Day15Solution::isClear(const Position &pos) const
{
    return warehouseMap[pos.y][pos.x] == SPACE;
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
        warehouseMap[nextPosition.y][nextPosition.x] = BOX;
        warehouseMap[object.y][object.x] = SPACE;
    }
}


vector<Day15Solution::Position> Day15Solution::findBoxes() const
{
    vector<Position> boxes;

    for (int y = 0; y < warehouseMap.size(); ++y)
        for (int x = 0; x < warehouseMap.size(); ++x)
            if (warehouseMap[y][x] == BOX)
                boxes.emplace_back(x, y);

    return boxes;
}


long long Day15Solution::twoStarSolution()
{
    int result {0};

    return result;
}
