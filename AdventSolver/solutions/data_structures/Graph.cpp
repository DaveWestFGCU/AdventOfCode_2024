/** Dev: Dave West
 * Date: December 10, 2024
 * Desc: Method definitions for a graph data structure.
**/

#include "Graph.h"


Graph::Graph(const vector<string> &input)
    : xBounds(input[0].length()), yBounds(input.size()), pathsFound(0)
{
    for (int y = 0; y < yBounds; ++y)
    {
        for (int x = 0; x < xBounds; ++x)
        {
            char tile = input[y][x];
            switch (tile)
            {
                case WALL:
                    continue;

                case PATH:
                    vertexes[{x,y}] = new Vertex(x,y,tile);
                    break;

                case START:
                    vertexes[{x,y}] = new Vertex(x,y,tile);
                    start = vertexes[{x,y}];
                    break;

                case END:
                    vertexes[{x,y}] = new Vertex(x,y,tile);
                    end = vertexes[{x,y}];
                    break;

                default: ;  // There should be no missed cases
            }

            if (vertexes.contains({x,y-1}))
            {
                vertexes[{x,y}]->adjacentVertexes[NORTH] = vertexes[{x,y-1}];
                vertexes[{x,y-1}]->adjacentVertexes[SOUTH] = vertexes[{x,y}];
            }

            if (vertexes.contains({x-1,y}))
            {
                vertexes[{x,y}]->adjacentVertexes[WEST] = vertexes[{x-1,y}];
                vertexes[{x-1,y}]->adjacentVertexes[EAST] = vertexes[{x,y}];
            }
        }
    }
}


void Graph::printGraph(const Reindeer &reindeer)
{
    for (size_t y = 0; y < yBounds; ++y)
    {
        for (size_t x = 0; x < xBounds; ++x)
        {
            if (!vertexes.contains({x, y}))
                std::cout << " ";
            else
            {
                if (x == reindeer.location->xPos &&
                    y == reindeer.location->yPos)
                {
                    switch (reindeer.facing)
                    {
                        case NORTH: std::cout << "^"; break;
                        case EAST:  std::cout << ">"; break;
                        case SOUTH: std::cout << "v"; break;
                        case WEST:  std::cout << "<"; break;
                        default:    std::cout << "?";
                    }
                }
                else
                std::cout << vertexes[{x, y}]->tileValue;
            }
        }
        std::cout << std::endl;
    }
}


int Graph::findShortestPathDistance(const std::pair<int, int> &start, const std::pair<int, int> &end)
{
    int currentDistance = 0;
    Reindeer reindeer(EAST, vertexes[start], vertexes[start]);

    // Reindeer starts facing east
    if(reindeer.location->adjacentVertexes[EAST])
    {
        reindeer.location = reindeer.location->adjacentVertexes[reindeer.facing];
        findShortestPaths(reindeer, currentDistance + 1);
    }

    if(reindeer.location->adjacentVertexes[SOUTH])
    {
        reindeer.facing = SOUTH;
        reindeer.location = reindeer.location->adjacentVertexes[reindeer.facing];
        findShortestPaths(reindeer, currentDistance + 1001);
    }

    if(reindeer.location->adjacentVertexes[WEST])
    {
        reindeer.facing = WEST;
        reindeer.location = reindeer.location->adjacentVertexes[reindeer.facing];
        findShortestPaths(reindeer, currentDistance + 2001);
    }

    if(reindeer.location->adjacentVertexes[NORTH])
    {
        reindeer.facing = NORTH;
        reindeer.location = reindeer.location->adjacentVertexes[reindeer.facing];
        findShortestPaths(reindeer, currentDistance + 1001);
    }
    std::cout << pathsFound << std::endl;;
    return this->end->minDistance;
}


void Graph::findShortestPaths(Reindeer reindeer, int currentDistance)
{
    //printGraph(reindeer);
    //string pause;
    //std::cin >> pause;

    // If a path has been found, stop looking if the distance is greater than that path.
    if (currentDistance > end->minDistance || currentDistance > reindeer.location->minDistance)
    {
        return;
    }

    // Reindeer got to this cell faster than prior, clear previous longer paths
    if (currentDistance < reindeer.location->minDistance)
    {
        reindeer.location->minDistance = currentDistance;
        reindeer.location->priorMinPathVertexes.clear();
        pathsFound = 0;
    }

    if (currentDistance == reindeer.location->minDistance)
    {
        // Only add one copy of the prior location
        bool priorTileNotInList = true;
        for (const auto &vertex : reindeer.location->priorMinPathVertexes)
            if (reindeer.lastLocation == vertex)
                priorTileNotInList = false;

        if (priorTileNotInList)
            reindeer.location->priorMinPathVertexes.push_back(reindeer.lastLocation);
    }

    // If reindeer is at the end, check if it's shorter than the shortest distance.
    // If so, it is now the shortest distance
    if (reindeer.location == end)
    {
        std::cout << end->minDistance << std::endl;
        ++pathsFound;
        return;
    }

    reindeer.lastLocation = reindeer.location;

    const auto right = static_cast<Direction>((static_cast<int>(reindeer.facing) + 1) % 4);
    Vertex *rightPath = reindeer.location->adjacentVertexes[right];

    const auto left = static_cast<Direction>((static_cast<int>(reindeer.facing) + 3) % 4);
    Vertex *leftPath = reindeer.location->adjacentVertexes[left];

    if (reindeer.location->adjacentVertexes[reindeer.facing])
    {
        reindeer.location = reindeer.location->adjacentVertexes[reindeer.facing];
        findShortestPaths(reindeer, currentDistance + 1);
    }

    if (leftPath)
    {
        reindeer.facing = left;
        reindeer.location = leftPath;
        findShortestPaths(reindeer, currentDistance + 1001);
    }

    if (rightPath)
    {
        reindeer.facing = right;
        reindeer.location = rightPath;
        findShortestPaths(reindeer, currentDistance + 1001);
    }
}


int Graph::countShortestPathTiles()
{
    Reindeer backtracker(EAST, end, end);
    int shortestPathTileCount {0};

    std::cout << "(" << backtracker.location->xPos << "," << backtracker.location->yPos << ")" << std::endl;

    for (auto tile : backtracker.location->priorMinPathVertexes)
    {
        backtracker.location = tile;
        backtrackShortestPaths(backtracker, shortestPathTileCount);
    }
    return shortestPathTileCount;
}


void Graph::backtrackShortestPaths(Reindeer backtracker, int &shortestPathTileCount)
{
    ++shortestPathTileCount;
    std::cout << "(" << backtracker.location->xPos << "," << backtracker.location->yPos << ")" << std::endl;

    if (backtracker.location == start)
    {
        std::cout << "Start found!" << std::endl;
        string pause;
        std::cin >> pause;
        return;
    }

    backtracker.lastLocation = backtracker.location;

    if (backtracker.location->priorMinPathVertexes.size() > 1)
    {
        std::cout << "Prior Vertexes: ";
        for (auto tile : backtracker.location->priorMinPathVertexes)
            std::cout << "(" << tile->xPos << "," << tile->yPos << ") ";
    }

    for (auto tile : backtracker.location->priorMinPathVertexes)
    {
        backtracker.location = tile;
        backtrackShortestPaths(backtracker, shortestPathTileCount);
    }
}