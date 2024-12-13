/*  Dev: Dave West
 * Date: December 10, 2024
 * Desc: Class declarations for a grid data structure.
 *       A grid is a graph representing a nxn matrix.
 */


#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <queue>

using std::vector, std::string;


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
    void visitVertex(char character, Vertex &visiting, vector<Vertex> &visited, std::queue<Vertex> &unvisited, int &perimeter);
    Vertex findUnvisitedVertex();

public:
    explicit Grid(const vector<string> &input);
    void printAdjacencyList();

        // AoC Day 12 Functionality
    int calcUnvisitedRegionCost();

        // Getters
    [[nodiscard]] size_t xSize() const { return xBounds; }
    [[nodiscard]] size_t ySize() const { return yBounds; }
    char getValue(size_t xPos, size_t yPos) { return adjacencyList[Vertex(xPos,yPos)].value; }
};


#endif //GRAPH_H
