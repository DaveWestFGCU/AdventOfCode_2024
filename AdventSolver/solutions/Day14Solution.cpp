/*  Dev: Dave West
 * Date: December 14, 2024
 * Desc: Method definitions for the AoC 2024 day 14 puzzle.
 */

#include "Day14Solution.h"


Day14Solution::Day14Solution(const vector<string> &puzzleInput)
    : title("--- Day 14: Restroom Redoubt ---")
{
    parseRobots(puzzleInput, 11, 7);
}


void Day14Solution::parseRobots(const vector<string> &puzzleInput, const int &xBound, const int &yBound)
{
    for (auto line : puzzleInput)
    {
        const std::regex pattern(R"(-?\d+)");
        std::sregex_iterator match(line.begin(), line.end(), pattern);
        int xPos = std::stoi(match->str());
        ++match;
        int yPos = std::stoi(match->str());
        ++match;
        int xVel = std::stoi(match->str());
        ++match;
        int yVel = std::stoi(match->str());
        robots.emplace_back(xPos, yPos, xVel, yVel, xBound, yBound);
    }
}


void Day14Solution::Robot::move(int seconds)
{
    position.x = (position.x + velocity.x * seconds) % bounds.x;
    while (position.x < 0)
        position.x += bounds.x;
    position.y = (position.y + velocity.y * seconds) % bounds.y;
    while (position.y < 0)
        position.y += bounds.y;
}



long long Day14Solution::oneStarSolution()
{
    int xBound, yBound;

    if (robots.size() < 20)
        xBound = 11, yBound = 7;
    else
        xBound = 101, yBound = 103;

    enum Quadrant {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
    int robotCount[4] = {0,0,0,0};
    for (auto robot : robots)
    {
        robot.setBounds(xBound, yBound);
        robot.move(100);
        if (robot.getY() < yBound/2)
        {
            if (robot.getX() < xBound/2)
                ++robotCount[TOP_LEFT];

            else if (robot.getX() > xBound/2)
                ++robotCount[TOP_RIGHT];
        }
        else if (robot.getY() > yBound/2)
        {
            if (robot.getX() < xBound/2)
                ++robotCount[BOTTOM_LEFT];

            else if (robot.getX() > xBound/2)
                ++robotCount[BOTTOM_RIGHT];
        }
    }

    int safetyFactor {1};

    for (const int &quadrant : robotCount)
        safetyFactor *= quadrant;

    return safetyFactor;
}


long long Day14Solution::twoStarSolution()
{
    int result {0};

    return result;
}
