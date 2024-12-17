/**  Dev: Dave West
 * Date: December 16, 2024
 * Desc: Class declarations for a graph data structure.
**/


#ifndef GRAPH_DS_H
#define GRAPH_DS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <set>

using std::vector, std::string;


class Graph
{
protected:
    enum Direction { NORTH, EAST, SOUTH, WEST };
    enum Tile { WALL = '#', PATH = '.', START = 'S', END = 'E' };
    struct Vertex
    {
        int xPos, yPos;
        char tileValue;
        Vertex *adjacentVertexes[4];
        int minDistance;
        vector<Vertex*> priorMinPathVertexes;
        Vertex()
            : xPos(-1), yPos(-1), tileValue('\0'), adjacentVertexes{nullptr,nullptr,nullptr,nullptr}, minDistance(INT_MAX) {}
        Vertex(const int &xPos, const int &yPos, const char &value)
            : xPos(xPos), yPos(yPos), tileValue(value), adjacentVertexes{nullptr,nullptr,nullptr,nullptr}, minDistance(INT_MAX) {}
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

    struct Reindeer { Direction facing; Vertex *location; Vertex *lastLocation; };

    size_t xBounds, yBounds;
    Vertex *start;
    Vertex *end;
    int pathsFound;

    std::unordered_map<std::pair<int,int>, Vertex*, PairHash> vertexes;
    void findShortestPaths(Reindeer reindeer, int currentDistance);
    void backtrackShortestPaths(Reindeer backtracker, int &shortestPathTileCount);

public:
    explicit Graph(const vector<string> &input);
    void printGraph(const Reindeer &reindeer);

    int findShortestPathDistance(const std::pair<int,int> &start, const std::pair<int,int> &end);
    int countShortestPathTiles();

    // Getters
    std::pair<int,int> getStartPosition() const { return {start->xPos, start->yPos}; }
    std::pair<int,int> getEndPosition() const { return {end->xPos, end->yPos}; }
};


#endif //GRAPH_DS_H
