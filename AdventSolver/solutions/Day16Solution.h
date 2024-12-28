/**  Dev: Dave West
 * Date: December 16, 2024
 * Desc: Class declarations for the AoC 2024 day 16 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 *       12/27/2024 - Completed two-star solution.
**/

#ifndef DAY16SOLUTION_H
#define DAY16SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

using std::set, std::queue, std::stack;


class Day16Solution : public Solution {
    string title;
    vector<string> puzzleInput;

    class Maze
    {
    protected:
        enum Direction { NORTH, EAST, SOUTH, WEST };
        enum Tile { WALL = '#', PATH = '.', START = 'S', END = 'E' };
        struct Vertex
        {
            int xPos, yPos;
            char tileValue;
            Vertex *adjacentVertexes[4];
            int minSteps;
            Vertex()
                    : xPos(-1), yPos(-1), tileValue('\0'), adjacentVertexes{nullptr,nullptr,nullptr,nullptr}, minSteps(INT_MAX) {}
            Vertex(const int &xPos, const int &yPos, const char &value)
                    : xPos(xPos), yPos(yPos), tileValue(value), adjacentVertexes{nullptr,nullptr,nullptr,nullptr}, minSteps(INT_MAX) {}
            bool operator== (const Vertex &vertex2) const { return xPos == vertex2.xPos && yPos == vertex2.yPos; }
        };

        struct PairHash
        {
            size_t operator()(const std::pair<int,int> &pair) const
            {
                size_t hash1 = std::hash<int>{}(pair.first);
                size_t hash2 = std::hash<int>{}(pair.second);

                return hash1 ^ (hash2 << 1);
            }
        };

        struct Reindeer
        {
            Direction facing;
            Vertex *location;
            int stepDistance;
            int numTurns;
            set<Vertex *> currentPath;

            Reindeer(Direction facing, Vertex *location, int stepDistance, int numTurns, set<Vertex *>currentPath)
                : facing(facing), location(location), stepDistance(stepDistance), numTurns(numTurns), currentPath(std::move(currentPath)) {}
        };

        struct compareDistance
        {
            bool operator()(const Reindeer &reindeer1, const Reindeer &reindeer2)
            {
                return reindeer1.stepDistance + reindeer1.numTurns*1000 > reindeer2.stepDistance + reindeer2.numTurns*1000;
            }
        };

        size_t xBounds, yBounds;
        Vertex *start;
        Vertex *end;
        int shortestPathScore;
        vector<set<Vertex *>> shortestPaths;

        std::unordered_map<std::pair<int,int>,Vertex *,PairHash> vertexes;
        void findShortestPaths(std::priority_queue<Reindeer,vector<Reindeer>, compareDistance> &priorityQueue);

    public:
        explicit Maze(const vector<string> &input);
        void printMaze(const Reindeer &reindeer);
        int findShortestPathDistance();
        int countShortestPathTiles();

        // Getters
        int getShortestPathScore() const { return shortestPathScore; }
    };
    Maze maze;

public:
    explicit Day16Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day16Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day16Solution>(puzzleInput);
    }
};



#endif //DAY16SOLUTION_H
