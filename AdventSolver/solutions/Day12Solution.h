/** Dev: Dave West
 * Date: December 12, 2024
 * Desc: Class declarations for the AoC 2024 day 12 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY12SOLUTION_H
#define DAY12SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <queue>


class Day12Solution : public Solution {
    string title;

    class Grid
    {
    protected:
        enum direction{ NORTH, EAST, SOUTH, WEST };
        struct Vertex
        {
            int xPos, yPos;
            Vertex() : xPos(-1), yPos(-1) {}
            Vertex(int xPos, int yPos) : xPos(xPos), yPos(yPos) {}
            bool operator== (const Vertex &vertex2) const
            {   return xPos == vertex2.xPos && yPos == vertex2.yPos;    }
        };


        struct VertexHash
        {
            size_t operator()(const Vertex &vertex) const
            {
                size_t hash1 = std::hash<int>{}(vertex.xPos);
                size_t hash2 = std::hash<int>{}(vertex.yPos);

                return hash1 ^ (hash2 << 1);
            }
        };

        struct VertexMapValue
        {
            char value;
            bool visited;
            bool inQueue;
            Vertex adjacentVertexes[4];
            VertexMapValue() : value('_'), visited(false), inQueue(false), adjacentVertexes() {}
            explicit VertexMapValue(char value) : value(value), visited(false), inQueue(false), adjacentVertexes() {}
            VertexMapValue(char value, Vertex adj[4]) : value(value), visited(false), inQueue(false), adjacentVertexes{adj[0],adj[1],adj[2],adj[3]} {}
        };

        size_t xBounds, yBounds;
        std::unordered_map<Vertex, VertexMapValue, VertexHash> adjacencyList;

        void buildAdjacencyList(const vector<string> &input);
        void visitVertex(char character, Vertex &visiting, vector<Vertex> &visited, std::queue<Vertex> &unvisited);
        Vertex findUnvisitedVertex();
        int findPerimeter(vector<Vertex> plot);
        int findSides(vector<Vertex> plot);


    public:
        explicit Grid(const vector<string> &input);
        void printAdjacencyList();

        // AoC Day 12 Functionality
        int calcUnvisitedRegionCost(bool bulkDiscount = false);

        // Getters
        [[nodiscard]] size_t xSize() const { return xBounds; }
        [[nodiscard]] size_t ySize() const { return yBounds; }
        char getValue(int xPos, int yPos) { return adjacencyList[Vertex(xPos,yPos)].value; }
    };

    Grid plotMap;

public:
    explicit Day12Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day12Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day12Solution>(puzzleInput);
    }
};



#endif //DAY12SOLUTION_H
