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
    struct Vertex
    {
        int xPos, yPos;
        Vertex(int xPos, int yPos) : xPos(xPos), yPos(yPos) {}
        Vertex(int xPos, int yPos, char value) : xPos(xPos), yPos(yPos) {}
        bool operator== (const Vertex &vertex2) const
        {   return xPos == vertex2.xPos && yPos == vertex2.yPos;    }
    };

    struct VertexHash
    {
        size_t operator()(const Vertex &vertex) const
        {
            size_t hashX = std::hash<int>{}(vertex.xPos);
            size_t hashY = std::hash<int>{}(vertex.yPos);
            return hashX ^ (hashY << 1);
        }
    };

    struct VertexMapValue
    {
        char value;
        bool visited;
        bool inQueue;
        vector<Vertex> adjacent;
        VertexMapValue() : value('\0'), visited(false) {}
        explicit VertexMapValue(char value) : value(value), visited(false) {}
        VertexMapValue(char value, vector<Vertex> adjacent) : value(value), visited(false), adjacent(std::move(adjacent)) {}
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
    size_t xSize() const { return xBounds; }
    size_t ySize() const { return yBounds; }
    char getValue(size_t xPos, size_t yPos) { return adjacencyList[Vertex(xPos,xPos)].value; }
};


#endif //GRAPH_H
