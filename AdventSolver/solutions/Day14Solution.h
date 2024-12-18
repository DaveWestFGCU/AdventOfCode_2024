/** Dev: Dave West
 * Date: December 14, 2024
 * Desc: Class declarations for the AoC 2024 day 14 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY14SOLUTION_H
#define DAY14SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <regex>


class Day14Solution : public Solution {
    string title;
    class Robot
    {
        struct Position { int x, y; } position;
        struct Velocity { int x, y; } velocity;
        struct Bounds   { int x, y; } bounds;

    public:
        Robot(const int &xPos, const int &yPos, const int &xVel, const int &yVel)
            : position(xPos, yPos), velocity(xVel, yVel), bounds(0,0) {};
        void move(int seconds);
        void setBounds(int xBound, int yBound) { bounds.x = xBound; bounds.y = yBound; }
        [[nodiscard]] int getX() const { return position.x; }
        [[nodiscard]] int getY() const { return position.y; }
    };
    vector<Robot> robots;

    void parseRobots(const vector<string> &puzzleInput);

    // Two-Star Methods
    int modInverse(int a, int m);

public:
    explicit Day14Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day14Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day14Solution>(puzzleInput);
    }
};



#endif //DAY14SOLUTION_H
