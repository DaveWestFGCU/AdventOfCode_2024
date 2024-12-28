/**  Dev: Dave West
 * Date: December 16, 2024
 * Desc: Method definitions for the AoC 2024 day 16 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 *       12/27/2024 - Completed two-star solution.
**/

#include "Day16Solution.h"
#include <iomanip>

Day16Solution::Day16Solution(const vector<string> &puzzleInput)
    : title("--- Day 16: Reindeer Maze ---"), maze(puzzleInput) {}


Day16Solution::Maze::Maze(const vector<string> &input)
        : xBounds(input[0].length()), yBounds(input.size()), shortestPathScore(INT_MAX)
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
                    start->minSteps = 0;
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


void Day16Solution::Maze::printMaze(const Reindeer &reindeer)
{
    for (int y = 0; y < yBounds; ++y)
    {
        for (int x = 0; x < xBounds; ++x)
        {
            if (vertexes.contains({x,y}))
            {
                if (reindeer.location->xPos == x & reindeer.location->yPos == y)
                    std::cout << "X" << std::setw(2) << vertexes[{x,y}]->minSteps;
                else if (vertexes[{x,y}]->minSteps == INT_MAX)
                    std::cout << std::setw(3) <<  " ";
                else
                    std::cout << std::setw(3)<< vertexes[{x,y}]->minSteps;
            }
            else
                std::cout << std::setw(3)<< "#";

        }
        std::cout << "\n";
    }
    // system("pause");
    // system("cls");
}


int Day16Solution::Maze::findShortestPathDistance()
{
    std::priority_queue<Reindeer,vector<Reindeer>, compareDistance> priorityQueue;

    // Reindeer starts facing east
    if(start->adjacentVertexes[EAST])
        priorityQueue.emplace(EAST, start->adjacentVertexes[EAST], 1, 0, set<Vertex *>{start});

    if(start->adjacentVertexes[SOUTH])
        priorityQueue.emplace(SOUTH, start->adjacentVertexes[SOUTH], 1,1, set<Vertex *>{start});

    if(start->adjacentVertexes[WEST])
        priorityQueue.emplace(WEST, start->adjacentVertexes[WEST], 1, 2, set<Vertex *>{start});

    if(start->adjacentVertexes[NORTH])
        priorityQueue.emplace(NORTH, start->adjacentVertexes[NORTH], 1,1, set<Vertex *>{start});

    findShortestPaths(priorityQueue);
    return shortestPathScore;
}


void Day16Solution::Maze::findShortestPaths(std::priority_queue<Reindeer,vector<Reindeer>, compareDistance> &priorityQueue)
{
    while (!priorityQueue.empty())
    {
        auto reindeer = priorityQueue.top();
        priorityQueue.pop();

        // printMaze(reindeer);
        // std::cout << reindeer.location->xPos << ", " << reindeer.location->yPos << " -> " << reindeer.distance << std::endl;

        // BASE CASE: Distance score is longer than the shortest path score.
        if (reindeer.stepDistance + reindeer.numTurns*1000 > shortestPathScore)
            continue;

        // BASE CASE: Reindeer has been to this tile before on this path.
        if (reindeer.stepDistance > reindeer.location->minSteps)
            continue;

        // BASE CASE: End is reached.
        if (reindeer.location == end)
        {
            // Clear previous best paths if the current path is shorter
            if (reindeer.stepDistance + reindeer.numTurns*1000 < shortestPathScore)
            {
                shortestPaths.clear();
                shortestPathScore =  reindeer.stepDistance + reindeer.numTurns*1000;
            }

            reindeer.currentPath.insert(reindeer.location);
            shortestPaths.push_back(reindeer.currentPath);

            continue;
        }


        // RECURSIVE CASE: Reindeer has not yet found the end
        reindeer.currentPath.insert(reindeer.location);

        // If the reindeer has gotten to this tile quicker than before, update the tile.
        if (reindeer.stepDistance < reindeer.location->minSteps)
            reindeer.location->minSteps = reindeer.stepDistance;

        const auto front = static_cast<Direction>(reindeer.facing);
        const auto left = static_cast<Direction>((static_cast<int>(reindeer.facing) + 3) % 4);
        const auto right = static_cast<Direction>((static_cast<int>(reindeer.facing) + 1) % 4);

        Vertex *frontPath = reindeer.location->adjacentVertexes[front];
        Vertex *leftPath = reindeer.location->adjacentVertexes[left];
        Vertex *rightPath = reindeer.location->adjacentVertexes[right];

        // If you can go straight, go straight
        if (frontPath)
            priorityQueue.emplace(front, frontPath, reindeer.stepDistance+1, reindeer.numTurns, reindeer.currentPath);

        // If there is a path to the left, go left.
        if (leftPath)
            priorityQueue.emplace(left, leftPath, reindeer.stepDistance+1, reindeer.numTurns+1, reindeer.currentPath);

        // If there is a path to the right, go right.
        if (rightPath)
            priorityQueue.emplace(right, rightPath, reindeer.stepDistance+1, reindeer.numTurns+1, reindeer.currentPath);


    }   // End while priority queue has elements.

}


string Day16Solution::oneStarSolution()
{
    return std::to_string(maze.findShortestPathDistance());
}


int Day16Solution::Maze::countShortestPathTiles()
{
    set<Vertex *> pathTiles;

    for (const auto &path : shortestPaths)
        for (const auto &tile : path)
            pathTiles.insert(tile);

    return static_cast<int>(pathTiles.size());
}


string Day16Solution::twoStarSolution()
{
    // Requires the one-star solution having been run first.
    if (maze.getShortestPathScore() == INT_MAX)
        maze.findShortestPathDistance();

    return std::to_string(maze.countShortestPathTiles());
}
