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
    enum Direction { NORTH = '^', EAST = '>', SOUTH = 'v', WEST = '<' };
    enum Tile { WALL = '#', SPACE = '.', ROBOT = '@', BOX = 'O', BOX_LEFT = '[', BOX_RIGHT = ']' };
    vector<string> initialMap;
    vector<string> warehouseMap;
    vector<Direction> moveInstructions;

    struct Position
    {
        int x, y;
        bool operator==(const Position &otherPosition) const
        {   return x == otherPosition.x && y == otherPosition.y;    }

        Position operator+(const Position &otherPosition) const
        {   return { 2*otherPosition.x - x, 2*otherPosition.y - y }; }
    };

    class Robot
    {
        vector<string> *warehouseMap;
        Position position{};
        [[nodiscard]] bool isBlocked(const Position &pos) const;
        [[nodiscard]] bool isClear(const Position &pos) const;
        Position getNextPosition(const Position &startPosition, const Direction &direction);
        bool pushIsClear(Position object, const Direction &direction);
        void pushBox(Position object, const Direction &direction);

    public:
        explicit Robot(vector<string> *warehouseMap)
            : warehouseMap(warehouseMap) {}

        [[nodiscard]] Position getPosition() const { return position; }
        [[nodiscard]] int getX() const { return position.x; }
        [[nodiscard]] int getY() const { return position.y; }
        void setPosition(const Position &newPosition) { position = newPosition; }
        void setPosition(const int &x, const int &y) { position.x = x; position.y = y; }

        void move(const Direction &direction);
    } robot;

    void parseInput(const vector<string> &puzzleInput);
    void setRobotInitialPosition();
    void printWarehouseState() const;

    // One-Star Methods
    void runMovementInstructions();
    [[nodiscard]] vector<Position> findBoxes() const;

    // Two-Star Methods
    void doubleWarehouseWidth();

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
