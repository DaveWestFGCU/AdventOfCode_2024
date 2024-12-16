/*  Dev: Dave West
 * Date: December 15, 2024
 * Desc: Class declarations for the AoC 2024 day 15 puzzle solution and solution factory.
 */

#ifndef DAY15SOLUTION_H
#define DAY15SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day15Solution : public Solution
{
    string title;
    vector<string> warehouseMap;
    string moveInstructions;
    enum Direction { NORTH = '^', EAST = '>', SOUTH = 'v', WEST = '<' };
    enum Tile { WALL = '#', SPACE = '.', ROBOT = '@', BOX = 'O' };
    struct Position
    {
        int x, y;
        bool operator==(Position otherPosition) const
        {
            return x == otherPosition.x && y == otherPosition.y;
        }
        Position operator+(const Position &otherPosition) const
        {
            return {
                2*otherPosition.x - x,
                2*otherPosition.y - y
            };
        }
    } robot{};

    void parseInput(const vector<string> &puzzleInput);
    void setRobotInitialPosition();
    void printWarehouseState() const;

    // One-Star Methods
    void runMovementInstructions();
    bool move(Position object, Position nextPosition);
    bool isBlocked(const Position &pos) const;
    bool isClear(const Position &pos) const;
    void moveObject(const Position &object, const Position &nextPosition);
    [[nodiscard]] vector<Position> findBoxes() const;

public:
    explicit Day15Solution(const vector<string> &puzzleInput);
    [[nodiscard]] string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day15Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day15Solution>(puzzleInput);
    }
};



#endif //DAY15SOLUTION_H
