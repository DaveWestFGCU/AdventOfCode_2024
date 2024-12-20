/** Dev: Dave West
* Date: December 20, 2024
 * Desc: Class declarations for the AoC 2024 day 20 puzzle solution and solution factory.
 */

#ifndef DAY20SOLUTION_H
#define DAY20SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <unordered_map>

class Day20Solution : public Solution {
    string title;
    enum Direction { NORTH, SOUTH, EAST, WEST };
    struct Position
    {
        int x, y;
        bool operator==(const Position &otherPosition) const
        {
            return x == otherPosition.x && y == otherPosition.y;
        }
        bool operator!=(const Position &otherPosition) const
        {
            return x != otherPosition.x || y != otherPosition.y;
        }
    };
    struct Hash_Position
    {
        size_t operator()(const Position &pos) const
        {
            size_t hashX = std::hash<int>{}(pos.x);
            size_t hashY = std::hash<int>{}(pos.y);
            return hashX ^ (hashY << 1);
        }
    };
    vector<string> racetrack;
    std::unordered_map<Position,int,Hash_Position> track;
    vector<Position> trackBySteps;
    Position startPosition, endPosition;

    void parseTrack();
    void runTrack();
    void printSteps();
    Position findNextPosition(const Position &current, const Position &last);

    int getTimeSaved(Position wall);
    vector<Position> getShortcutEndpoints(const Position &first, const int &maxShortcutDuration, const int &minImprovement);

public:
    explicit Day20Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day20Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day20Solution>(puzzleInput);
    }
};


#endif //DAY20SOLUTION_H
