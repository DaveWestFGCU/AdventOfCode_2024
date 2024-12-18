/** Dev: Dave West
 * Date: December 12, 2024
 * Desc: Method definitions for the AoC 2024 day 12 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#include "Day12Solution.h"


Day12Solution::Day12Solution(const vector<string> &puzzleInput)
    : title("--- Day 12: Garden Groups ---"),
      plotMap(puzzleInput)
{}


string Day12Solution::oneStarSolution()
{
    long long totalPrice {0};
    int regionCost;
    do {
        regionCost = plotMap.calcUnvisitedRegionCost();
        totalPrice += regionCost;
    } while (regionCost);

    return std::to_string(totalPrice);
}


string Day12Solution::twoStarSolution()
{
    long long totalPrice {0};
    int regionCost;
    do {
        regionCost = plotMap.calcUnvisitedRegionCost(true);
        totalPrice += regionCost;
    } while (regionCost);

    return std::to_string(totalPrice);
}
