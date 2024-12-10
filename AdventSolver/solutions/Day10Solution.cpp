/*  Dev: Dave West
 * Date: December 10, 2024
 * Desc: Method definitions for the AoC 2024 day 10 puzzle.
 */

#include "Day10Solution.h"


Day10Solution::Day10Solution(const vector<string> &puzzleInput)
    : title("--- Day 10: Hoof It ---")
{
    buildMap(puzzleInput);
    mapXBound = topographicalMap.size();
    mapYBound = topographicalMap[0].size();
    findNeighbors();
}


void Day10Solution::buildMap(const vector<string> &input)
{
    for (int x = 0; x < input[0].length(); ++x)
    {
        vector<Vertex> mapRow;
        int yPos{0};
        for (int y = static_cast<int>(input.size())-1; y >= 0; --y)
            mapRow.emplace_back(x, yPos++, input[y][x] - '0');

        topographicalMap.push_back(mapRow);
    }
    printMap();
}


void Day10Solution::printMap() const
{
    for (int y = static_cast<int>(topographicalMap.size())-1; y >= 0 ; --y)
    {
        for (int x = 0; x < topographicalMap.size(); ++x)
            std::cout << topographicalMap[x][y].value;

        std::cout << std::endl;
    }
}


void Day10Solution::findNeighbors()
{

    for (int y = 0; y < topographicalMap.size(); ++y)
        for (int x = 0; x < topographicalMap[y].size(); ++x)
        {
            Vertex *currentVertex = &topographicalMap[x][y];

            if (x > 0)
                if (currentVertex->value + 1 == topographicalMap[x-1][y].value)
                    currentVertex->neighbors.push_back(&topographicalMap[x-1][y]);

            if (y > 0)
                if (currentVertex->value + 1 == topographicalMap[x][y-1].value)
                currentVertex->neighbors.push_back(&topographicalMap[x][y-1]);

            if (x < mapXBound - 1)
                if (currentVertex->value + 1 == topographicalMap[x+1][y].value)
                    currentVertex->neighbors.push_back(&topographicalMap[x+1][y]);

            if (y < mapYBound - 1)
                if (currentVertex->value + 1 == topographicalMap[x][y+1].value)
                    currentVertex->neighbors.push_back(&topographicalMap[x][y+1]);

            std::cout << "(" << x << "," << y << "): ";
            for (auto neighbor : currentVertex->neighbors)
                std::cout << neighbor->value << "(" << neighbor->xPos << "," << neighbor->yPos << "), ";
            std::cout << std::endl;
        }
}



long long Day10Solution::oneStarSolution()
{
    int result {0};


    for (int y = 0; y < topographicalMap.size(); ++y)
        for (int x = 0; x < topographicalMap[y].size(); ++x)
            if (topographicalMap[x][y].value == 0)
            {
                int score = depthFirstSearch(&topographicalMap[x][y]);
                std::cout << "Trailhead score: " << score << std::endl;
                result += score;
                resetVertices();
            }

    return result;
}


size_t Day10Solution::depthFirstSearch(Vertex *vertex)
{
    std::cout << "[(" << vertex->xPos << "," << vertex->yPos << "): " << vertex->value << "]" << std::endl;
    // Base case: Found a complete path
    if (vertex->value == 9 && !vertex->visited)
    {
        std::cout << "Path found!" << std::endl;
        vertex->visited = true;
        return 1;
    }

    // Base case: Dead end
    if (vertex->neighbors.empty())
    {
        std::cout << "Dead end" << std::endl;
        return 0;
    }

    // Recursive case: Check each viable neighbor.
    size_t score{0};
    for (auto neighbor : vertex->neighbors)
        score += depthFirstSearch(neighbor);
    return score;
}

void Day10Solution::resetVertices()
{
    for (int y = 0; y < mapYBound; ++y)
        for (int x = 0; x < mapXBound; ++x)
            topographicalMap[x][y].visited = false;
}



long long Day10Solution::twoStarSolution()
{
    int result {0};

    return result;
}
