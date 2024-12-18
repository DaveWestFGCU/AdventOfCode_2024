/**  Dev: Dave West
 * Date: December 16, 2024
 * Desc: Method definitions for the AoC 2024 day 16 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
**/

#include "Day16Solution.h"


Day16Solution::Day16Solution(const vector<string> &puzzleInput)
    : title("--- Day 16: Reindeer Maze ---"), maze(puzzleInput)
{
}


string Day16Solution::oneStarSolution()
{
    return std::to_string(maze.findShortestPathDistance(maze.getStartPosition(), maze.getEndPosition()));
}


string Day16Solution::twoStarSolution()
{
    return std::to_string(maze.countShortestPathTiles());
}
