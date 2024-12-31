/** Dev: Dave West
 * Date: December 1, 2024
 * Desc: Class declarations for the AoC 2024 day 1 puzzle solution and solution factory.
 *  Log: 12/ 1/2024 - Completed solution.
 *       12/ 4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/ 7/2024 - Refactored integer to long long or size_t.
 *                    Refactored puzzle parsing from regex to stringstream.
 *       12/17/2024 - Refactored one and two-star solutions to return strings.
 *       12/19/2024 - Refactored two-star solution to use a switch-case in choosing a data structure to use.
 *       12/30/2024 - Added comments.
 */

#ifndef DAY1SOLUTION_H
#define DAY1SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

/**
 * Class for solving the 2024 Advent of Code day 1 puzzle.
 */
class Day1Solution : public Solution {
    enum SolutionDataStructure { SORTED_LISTS, MAP, UNORDERED_MAP };    //  Different data structures that can be used in the solveTwoStarProblem() function.
    std::string title;  // Puzzle Title
    std::vector<size_t> leftList, rightList;    // Two lists of locations derived from the puzzle input.

    /**
     * Splits the puzzle input into a left list and right list.
     * @param inputList Puzzle input for day 1.
     */
    void splitList(const vector<string> &inputList);

    /**
     * Solves the two-star problem. Can be solved with one of three data structures.
     * @param dataStructure Enum for the data structure to use in solving.
     * @return Solution for the two-star puzzle.
     */
    size_t solveTwoStarProblem(const SolutionDataStructure &dataStructure);

    /**
     * Solves the two-star puzzle using a map (O(log n) search).
     * @return Solution for the two-star puzzle.
     */
    size_t twoStarsMap();

    /**
     * Solves the two-star puzzle using the sorted lists from the one-star puzzle.
     * @return Solution for the two-star puzzle.
     */
    size_t twoStarsPreSortedLists();

    /**
     * Solves the two-star puzzle using an unordered map (O(1) search).
     * @return
     */
    size_t twoStarsUnorderedMap();

public:
    /**
     * Constructor for the day 1 puzzle solver.
     * @param puzzleInput Puzzle input for day 1.
     */
    explicit Day1Solution(const vector<string> &puzzleInput);

    /**
     * Getter for the day's puzzle title.
     * @return The puzzle's title.
     */
    [[nodiscard]] std::string getTitle() const override { return title; }

    /**
     * Solves the one-star part of the day's puzzle.
     * @return The one-star solution.
     */
    string oneStarSolution() override;

    /**
     * Solves the two-star part of the day's puzzle.
     * @return The two-star solution.
     */
    string twoStarSolution() override;
};


/**
 * Day1Solution factory class.
 */
class Day1Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day1Solution>(puzzleInput);
    }
};

#endif //DAY1SOLUTION_H
