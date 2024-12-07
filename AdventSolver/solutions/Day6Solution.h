

#ifndef DAY6SOLUTION_H
#define DAY6SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <unordered_map>
#include <utility>

using std::vector, std::string;

class Day6Solution : public Solution {

    enum Direction {NORTH, EAST, SOUTH, WEST, ERROR = -1};
    class Guard
    {
    public:
        enum GuardStatus {PATROLING, LEFT_AREA, LOOPING};
    private:
        struct Location {int y, x;};
        std::unordered_map<string, vector<bool>> seenObstructions;
        GuardStatus status;
        vector<string> roomMap;
        Direction facing;
        Location location{};
        vector<vector<bool>> visitedMap;


        void setGuardLocation();
        void buildVisitedMap();
        void printMap(const vector<string> & patrolMap);

            // Patrol Methods
        bool isBlocked(const vector<string>& patrolMap);
        bool isOutOfBounds(const vector<string>& patrolMap);
        bool inLoop();

    public:
        explicit Guard(const vector<string>& puzzleInput);

        GuardStatus patrol(vector<string> patrolMap);
        GuardStatus patrol() {return patrol(roomMap);}
        void turn();
        void move();
        size_t countVisitedLocations();
        vector<std::pair<int,int>> getVisitedLocations();

        void reset();
        GuardStatus getStatus() {return status;}
    };

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
