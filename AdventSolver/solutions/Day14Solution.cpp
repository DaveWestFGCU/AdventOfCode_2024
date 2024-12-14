/*  Dev: Dave West
 * Date: December 14, 2024
 * Desc: Method definitions for the AoC 2024 day 14 puzzle.
 */

#include "Day14Solution.h"


Day14Solution::Day14Solution(const vector<string> &puzzleInput)
    : title("--- Day 14: Restroom Redoubt ---")
{
    parseRobots(puzzleInput);
}


void Day14Solution::parseRobots(const vector<string> &puzzleInput)
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
        robots.emplace_back(xPos, yPos, xVel, yVel);
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


/**
 * This solution comes from reddit.com/u/i_have_no_biscuits and is an application of the Chinese Remainder Theorem.
 * @return
 */
long long Day14Solution::twoStarSolution()
{
    // Set bounds for example vs puzzle
    const int xBound = robots.size() < 20 ? 11 : 101;
    const int yBound = robots.size() < 20 ? 7  : 103;

    for (auto &robot : robots)
        robot.setBounds(xBound, yBound);

    int seconds = 1;
    int lastMove {0};

    /* Visually inspecting grids at every second, there are patterns of
     * horizontal band clustering every 31 + n * yBound iterations (31, 134, 237, ...) and
     * vertical band clustering every 72 + m * xBound iterations (72, 173, 274, ...).
     * I think when these banding patterns overlap there will be a Christmas tree pattern.
     *
     * (There is!)
     */

    /* Looping through every second and checking if the two patterns are occurring simultaneously was the way I reasoned
     * out how to do it. Apparently there is a Chinese Remainder Theorem that will give you the ability to determine
     * this mathematically.
     */
    while (seconds < xBound * yBound)    //  Will have returned to initial state after (at most) xBound*yBound steps
    {

        if ((seconds-72) % 101 == 0 && (seconds-31) % 103 == 0)
            return seconds;


        // Everything after this point is for a visual representation of the robots' positions at this time.
    /*  if ((seconds-72) % 101 == 0 && (seconds-31) % 103 == 0)
        {
            // Set grid
            char grid[xBound][yBound];
            for (int y = 0; y < yBound; ++y)
                for (int x = 0; x < xBound; ++x)
                    grid[x][y] = ' ';

            for (auto &robot : robots)
            {
                robot.move(seconds - lastMove);
                grid[robot.getX()][robot.getY()] = 'R';
            }
            lastMove = seconds;

            std::cout << std::endl << "------------------------------------------------" << seconds << "------------------------------------------------" << std::endl;

            for (int y = 0; y < yBound; ++y)
            {
                for (int x = 0; x < xBound; ++x)
                    std::cout << grid[x][y];
                std::cout << std::endl;
            }
            std::cout << std::endl;

            string pause;
            std::cin >> pause;

            system("pause");
        }
    */
        seconds++;
    }

    return 0;
}
