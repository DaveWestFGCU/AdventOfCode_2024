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


//template <typename T>
void Grid::buildAdjacencyList(const vector<string> &input)
{
        // Add each vertex to the map's keys
    for (size_t y = 0; y < yBounds; ++y)
    {
        for (size_t x = 0; x < xBounds; ++x)
        {
            // Add map key
            adjacencyList[Vertex(x, y)];
        }
    }

        // Add map values (pointers to adjacent vertexes)
    for (int y = 0; y < yBounds; ++y)
    {
        for (int x = 0; x < xBounds; ++x)
        {
            Vertex adjacentVertexes[4];
            adjacentVertexes[NORTH] = y == 0         ? Vertex(-1,-1) : Vertex(x, y-1);
            adjacentVertexes[EAST]  = x == xBounds-1 ? Vertex(-1,-1) : Vertex(x+1, y);
            adjacentVertexes[SOUTH] = y == yBounds-1 ? Vertex(-1,-1) : Vertex(x, y+1);
            adjacentVertexes[WEST]  = x == 0         ? Vertex(-1,-1) : Vertex(x-1, y);

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

            for (int direction = NORTH; direction <= WEST; ++direction)
            {
                Vertex adjacentVertex = adjacencyList[vertex].adjacentVertexes[direction];
                if (adjacentVertex != Vertex(-1,-1))
                    std::cout << "(" << adjacentVertex.xPos << "," << adjacentVertex.yPos << ") " << adjacencyList[adjacentVertex].value;
                if (direction != WEST)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    }
}


/**
 * Solution for Day 12 Part 1
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

    char value = adjacencyList[startVertex].value;

    vector<Vertex> visited;

    int perimeter {0};

    while (!unvisited.empty())
    {
        Vertex visiting = unvisited.front();
        unvisited.pop();
        visitVertex(value, visiting, visited, unvisited, perimeter);
    }

    int area = visited.size();
    std::cout << " -> A: " << area << " x P: " << perimeter << " = " << area * perimeter << std::endl;
    return area * perimeter;
}


void Grid::visitVertex(char value, Vertex &visiting, vector<Vertex> &visited, std::queue<Vertex> &unvisited, int &perimeter)
{
    adjacencyList[visiting].visited = true;
    visited.push_back(visiting);
    // Add to adjacent nodes to unvisited queue if not visited and match the character
    auto adjacentVertexes = adjacencyList[visiting].adjacentVertexes;
    for (int direction = NORTH; direction <= WEST; ++direction)
    {
        auto adjacentVertex = adjacentVertexes[direction];
        if (!adjacencyList[adjacentVertex].visited && !adjacencyList[adjacentVertex].inQueue)
        {
            if (adjacencyList[adjacentVertex].value == value)
            {
                unvisited.push(adjacentVertex);
                adjacencyList[adjacentVertex].inQueue = true;
            }
        }

            // Inner boundary checking
        if (adjacencyList[adjacentVertex].value != value && adjacentVertex != Vertex(-1,-1))
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
    for (int y = 0; y < yBounds; ++y)
    {
        for (int x = 0; x < xBounds; ++x)
        {
            if (!adjacencyList[Vertex(x,y)].visited)
                return {x, y};
        }
    }
    return {-1, -1};
}





