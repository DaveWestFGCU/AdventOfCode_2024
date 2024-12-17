/**  Dev: Dave West
 * Date: December 16, 2024
 * Desc: Method definitions for the AoC 2024 day 16 puzzle.
**/

#include "Day16Solution.h"


Day16Solution::Day16Solution(const vector<string> &puzzleInput)
    : title("--- Day 16: Reindeer Maze ---"), maze(puzzleInput)
{
}


long long Day16Solution::oneStarSolution()
{
    return maze.findShortestPathDistance(maze.getStartPosition(), maze.getEndPosition());
}


long long Day16Solution::twoStarSolution()
{
    return maze.countShortestPathTiles();
}
