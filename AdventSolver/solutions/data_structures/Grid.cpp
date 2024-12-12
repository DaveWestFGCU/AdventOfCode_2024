/*  Dev: Dave West
 * Date: December 10, 2024
 * Desc: Method definitions for a grid data structure.
 *       A grid is a graph representing a nxn matrix.
 */

#include "Grid.h"

Grid::Grid(const vector<string> &input)
    : xBounds(input[0].length()), yBounds(input.size())
{
    buildAdjacencyList(input);
}


void Grid::buildAdjacencyList(const vector<string> &input)
{
        // Add each vertex to the map's keys
    for (size_t y = 0; y < yBounds; ++y)
    {
        for (size_t x = 0; x < xBounds; ++x)
        {
            // Add map key
            adjacencyList[Vertex(x, y, input[y][x])];
        }
    }

        // Add map values (pointers to adjacent vertexes)
    for (size_t y = 0; y < yBounds; ++y)
    {
        for (size_t x = 0; x < xBounds; ++x)
        {
            vector<Vertex> adjacentVertexes;
            if (y != 0)
                adjacentVertexes.emplace_back(x, y-1);
            if (x != 0)
                adjacentVertexes.emplace_back(x-1, y);
            if (y != input.size()-1)
                adjacentVertexes.emplace_back(x, y+1);
            if (x != input[x].length()-1)
                adjacentVertexes.emplace_back(x+1, y);

            adjacencyList[Vertex(x,y)] = VertexMapValue(input[y][x], adjacentVertexes);
        }
    }
}


void Grid::printAdjacencyList()
{
    for (size_t y = 0; y < yBounds; ++y)
    {
        for (size_t x = 0; x < xBounds; ++x)
        {
            auto vertex = Vertex(x,y);
            std::cout << "[" << x << "," << y << "] " << adjacencyList[vertex].value << " | ";

            for (const auto &adjacentVertex : adjacencyList[vertex].adjacent)
                std::cout << "(" << adjacentVertex.xPos << "," << adjacentVertex.yPos << ") " << adjacencyList[adjacentVertex].value << " -> ";

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


/**
 * Solution for Day 12 Part 1
 * Loads 'section' with a vector of vertexes that are touching and have the same value.
 * @param character First unvisited char found.
 * @param section List of vertexes that have a value of that char that are contiguous.
 */
int Grid::calcUnvisitedRegionCost()
{
    Vertex startVertex = findUnvisitedVertex();
    std::cout << std::endl;
    if (startVertex == Vertex(-1,-1))   //  No unvisited characters found.
    {
        return 0;
    }

    std::queue<Vertex> unvisited;
    unvisited.push(startVertex);

    char character = adjacencyList[startVertex].value;
    std::cout << "Character: " << character;
    vector<Vertex> visited;

    int perimeter {0};

    while (!unvisited.empty())
    {
        Vertex visiting = unvisited.front();
        unvisited.pop();
        visitVertex(character, visiting, visited, unvisited, perimeter);
    }

    int area = visited.size();
    std::cout << " -> A: " << area << " x P: " << perimeter << " = " << area * perimeter << std::endl;
    return area * perimeter;
}


void Grid::visitVertex(char character, Vertex &visiting, vector<Vertex> &visited, std::queue<Vertex> &unvisited, int &perimeter)
{
    adjacencyList[visiting].visited = true;
    visited.push_back(visiting);

    // Add to adjacent nodes to unvisited queue if not visited and match the character
    for (auto vertex : adjacencyList[visiting].adjacent)
    {
        if (!adjacencyList[vertex].visited && !adjacencyList[vertex].inQueue)
        {
            if (adjacencyList[vertex].value == character)
            {
                unvisited.push(vertex);
                adjacencyList[vertex].inQueue = true;
            }
        }

            // Inner boundary checking
        if (adjacencyList[vertex].value != character)
            ++perimeter;
    }

    // Outer boundary checking
    if (visiting.xPos == 0 || visiting.xPos == xBounds-1)
        ++perimeter;
    if (visiting.yPos == 0 || visiting.yPos == yBounds-1)
        ++perimeter;
}


/**
 * Finds an unvisited vertex in the grid.
 * @return If found, returns a Vertex to the first position in the first line found. If not found, returns a Vertex(-1,-1).
 */
Grid::Vertex Grid::findUnvisitedVertex()
{
    for (size_t y = 0; y < yBounds; ++y)
    {
        for (size_t x = 0; x < xBounds; ++x)
        {
            if (!adjacencyList[Vertex(x,y)].visited)
                return {static_cast<int>(x), static_cast<int>(y)};
        }
    }
    return {-1, -1};
}





