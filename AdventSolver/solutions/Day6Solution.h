/*  Dev: Dave West
* Date: December 6, 2024
 * Desc: Method definitions for the AoC 2024 day 6 puzzle.
 */

#ifndef DAY6SOLUTION_H
#define DAY6SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <unordered_map>
#include <utility>

using std::vector, std::string;

class Day6Solution : public Solution {

    enum Direction {NORTH, EAST, SOUTH, WEST};
    class Guard
    {
    public:
        enum GuardStatus {PATROLING, LEFT_AREA, LOOPING};
    private:
        struct Location {int y, x;};
        std::unordered_map<string, vector<bool>> seenObstructions;
        GuardStatus status;
        vector<string> roomMap;     // Puzzle input with or without extra obstacle
        Direction facing;
        Location location{};
        vector<vector<bool>> visitedMap;    // Map of locations visited by the guard.


        void setGuardLocation();
        void buildVisitedMap();
        void printMap(const vector<string> & patrolMap);

            // Patrol Methods
        bool isBlocked(const vector<string>& patrolMap);
        bool isOutOfBounds(const vector<string>& patrolMap);
        bool inLoop();

    public:
        explicit Guard(const vector<string>& puzzleInput);

        GuardStatus patrol(const vector<string>& patrolMap);
        GuardStatus patrol() {return patrol(roomMap);}
        void turn();
        void move();
        size_t countVisitedLocations();
        vector<std::pair<int,int>> getVisitedLocations();

        void reset();
        GuardStatus getStatus() const {return status;}
    };

    string title;
    vector<string> puzzleInput;
    Guard guardBob;

        // One-star methods
    size_t countVisitedLocations();

        // Two-Star Methods
    size_t bruteForcedTwoStar();
    size_t optimizedTwoStar();

public:
    explicit Day6Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day6Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day6Solution>(puzzleInput);
    }
};

#endif //DAY6SOLUTION_H
