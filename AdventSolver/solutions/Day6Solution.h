

#ifndef DAY6SOLUTION_H
#define DAY6SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <tuple>

using std::vector, std::string;

class Day6Solution : public Solution {

    enum Direction {NORTH, SOUTH, EAST, WEST, ERROR = -1};
    class Guard
    {
    public:
        enum GuardStatus {PATROLING, LEFT_AREA, LOOPING};
    private:
        struct Location {int y, x;};
        struct Visited
        {
            bool atLeastOnce;
            bool facingList[4];
        };

        GuardStatus status;
        vector<string> roomMap;
        Direction facing;
        Location location{};
        vector<vector<Visited>> visitedMap;

        void setGuardLocation();
        void buildVisitedMap();
        void printMap();

            // Patrol Methods
        bool isBlocked(vector<string> patrolMap);
        bool foundCycle();

    public:
        explicit Guard(const vector<string>& puzzleInput);

        void patrol(vector<string> patrolMap);
        void patrol() {return patrol(roomMap);}
        size_t countVisitedLocations();

        void reset();
        GuardStatus getStatus() {return status;}
    };
    friend class Guard;

    string title;
    vector<string> puzzleInput;
    Guard guardBob;

        // One-star methods
    size_t countVisitedLocations();

        // Two-Star Methods
    void addObstruction(size_t xLoc, size_t yLoc);
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

#endif //DAY3SOLUTION_H
