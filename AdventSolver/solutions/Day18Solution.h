/** Dev: Dave West
 * Date: December 18, 2024
 * Desc: Class declarations for the AoC 2024 day 18 puzzle solution and solution factory.
 */

#ifndef DAY18SOLUTION_H
#define DAY18SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <queue>


class Day18Solution : public Solution {
    string title;
    vector<std::pair<int,int>> corruptedMemoryLocations;
    int xBounds{}, yBounds{};
    enum Direction { NORTH, EAST, SOUTH, WEST };
    struct MemoryLoc
    {
        int x, y;
        char value;
        bool safe;
        bool queued;
        bool visited;
        MemoryLoc *neighbor[4];
        MemoryLoc() = default;
        MemoryLoc(const int &x, const int &y, const char &value) : x(x), y(y), value(value), safe(true), queued(false), visited(false), neighbor{nullptr,nullptr,nullptr,nullptr} {}
    };
    vector<vector<MemoryLoc>>memoryMap;

    void parseCorruptedMemory(const vector<string> &puzzleInput);
    void printCorruptedMemory();
    void buildMemoryMap(const int &fallenMemoryTotal);
    void printMemoryMap();

    int findShortestPath(int searchX, int searchY);
    int findFirstPathInterruption(int leftIndex, int rightIndex, int shortestPathLengths[]);
public:
    explicit Day18Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day18Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day18Solution>(puzzleInput);
    }
};



#endif //DAY18SOLUTION_H
