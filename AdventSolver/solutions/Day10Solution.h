/*  Dev: Dave West
 * Date: December 10, 2024
 * Desc: Class declarations for the AoC 2024 day 10 puzzle solution and solution factory.
 */

#ifndef DAY10SOLUTION_H
#define DAY10SOLUTION_H

#include "../AdventSolver.h"
#include "Solution.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day10Solution : public Solution {
    string title;
    enum Direction { NONE, NORTH, EAST, SOUTH, WEST };
    struct Vertex
    {
        int xPos, yPos, value;
        vector<Vertex*> neighbors;
        bool visited;

        explicit Vertex(int xPos, int yPos, int value)
            : xPos(xPos), yPos(yPos), value(value), visited(false){};
    };
    vector<vector<Vertex>> topographicalMap;

    size_t mapXBound, mapYBound;
    vector<std::pair<size_t,size_t>> trailheadLocations;

    void buildMap(const vector<string> &input);
    void printMap() const;
    void findNeighbors();

        //  One-Star Methods
    size_t depthFirstSearch(Vertex *vertex, const bool &includeRatings = false);
    void resetVertices();

public:
    explicit Day10Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day10Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day10Solution>(puzzleInput);
    }
};


#endif //DAY10SOLUTION_H
