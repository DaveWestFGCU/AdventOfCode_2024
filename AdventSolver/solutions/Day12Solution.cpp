/*  Dev: Dave West
 * Date: December 12, 2024
 * Desc: Method definitions for the AoC 2024 day 12 puzzle.
 */

#include "Day12Solution.h"


Day12Solution::Day12Solution(const vector<string> &puzzleInput)
    : title("--- Day 12: Garden Groups ---"),
      plotMap(puzzleInput)
{
    // plotMap.printAdjacencyList();
}


long long Day12Solution::oneStarSolution()
{
    long long totalPrice {0};
    int regionCost;
    do {
        regionCost = plotMap.calcUnvisitedRegionCost();
        totalPrice += regionCost;
    } while (regionCost);

    return totalPrice;
}


long long Day12Solution::twoStarSolution()
{
    int result {0};

    return result;
}
