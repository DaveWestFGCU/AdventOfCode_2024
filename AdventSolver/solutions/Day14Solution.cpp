/** Dev: Dave West
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


string Day14Solution::oneStarSolution()
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

    return std::to_string(safetyFactor);
}


/**
 * This is my initial, brute-force-adjacent solution (it doesn't render grids for every second, but it checks every
 * second for whether overlapping pattern criteria are met.
 * When visually inspecting robot locations at every second, I noticed there are patterns of
 * horizontally clustered bands every n(yBound) + 31 iterations (31, 134, 237, ...),
 * and vertically clustered bands every m(xBound) + 72 iterations (72, 173, 274, ...).
 * So my thought was that when these two patterns overlap, we have our Christmas tree.
 * This function loops every second and checks for whether that second fits the above criteria.
 * If it does, print a representation of robot positions for confirmation and return the number of seconds it took.
 */
/*long long Day14Solution::twoStarSolution()
{
    // Set bounds for example vs puzzle
    const int xBound = robots.size() < 20 ? 11 : 101;
    const int yBound = robots.size() < 20 ? 7  : 103;

    for (auto &robot : robots)
        robot.setBounds(xBound, yBound);

    int seconds = 1;
    while (seconds < xBound * yBound)    //  Will have returned to initial state after (at most) xBound*yBound steps
    {

        if ((seconds-72) % 101 == 0 && (seconds-31) % 103 == 0)

        // Everything after this point is for a visual representation of the robots' positions at this time.
        if ((seconds-72) % 101 == 0 && (seconds-31) % 103 == 0)
        {
            // Set grid
            char grid[xBound][yBound];
            for (int y = 0; y < yBound; ++y)
                for (int x = 0; x < xBound; ++x)
                    grid[x][y] = ' ';

            for (auto &robot : robots)
            {
                robot.move(seconds);
                grid[robot.getX()][robot.getY()] = 'R';
            }

            for (int y = 0; y < yBound; ++y)
            {
                for (int x = 0; x < xBound; ++x)
                    std::cout << grid[x][y];
                std::cout << std::endl;
            }
            std::cout << std::endl;

            return seconds;
        }

        seconds++;
    }

    return -1;
}
*/


/**
 * I had recognised the initial equations, but could not deduce an equation to solve for iteration that
 * would make them equal.
 * This optimized solution comes from Reddit user i_have_no_biscuits and is an application of the
 * Chinese Remainder Theorem. (https://www.reddit.com/r/adventofcode/comments/1he0asr/comment/m1zzfsh/)
 * "
 * time = best_x (mod Width)
 * time = best_y (mod Height)
 *
 * As time = best_x (mod Width), then time = best_x + k*Width. Substituting this into the second equation we get
 *
 * best_x + k*Width = best_y (mod Height)
 * k*Width = best_y - best_x (mod Height)
 * k = inverse(Width)*(best_y - best_x) (mod Height)
 *
 * and so, finally,
 *
 * time = best_x + inverse(Width)*(best_y-best_x)*Width
 * "
 */
string Day14Solution::twoStarSolution()
{
    // Set bounds for example vs puzzle
    const int xBound = robots.size() < 20 ? 11 : 101;
    const int yBound = robots.size() < 20 ? 7  : 103;

    const int width = xBound;
    const int height = yBound;
    const int best_x = 72;
    const int best_y = 31;

    int thatMiddleBit = (modInverse(width,height) * (best_y-best_x)) % height;
    thatMiddleBit = thatMiddleBit > 0 ? thatMiddleBit : thatMiddleBit + height;

    const int time = best_x + thatMiddleBit * width;
    return std::to_string(time);
}


int Day14Solution::modInverse(int a, int m)
{
    int m_0 = m, t, q;
    int x_0 = 0, x_1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x_0;
        x_0 = x_1 - q * x_0;
        x_1 = t;
    }

    if (x_1 < 0)
        x_1 += m_0;

    return x_1;
}

