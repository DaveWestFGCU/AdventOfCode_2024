/** Dev: Dave West
 * Date: December 1, 2024
 * Desc: Class declarations for the AoC 2024 day 1 puzzle solution and solution factory.
 *  Log: 12/ 1/2024 - Completed solution.
 *       12/ 4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/ 7/2024 - Refactored integer to long long or size_t.
 *                    Refactored puzzle parsing from regex to stringstream.
 *       12/17/2024 - Refactored one and two star solutions to return strings.
 *       12/19/2024 - Refactored two-star solution to use a switch-case in choosing a data structure to use.
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

class Day1Solution : public Solution {
    enum SolutionDataStructure { SORTED_LISTS, MAP, UNORDERED_MAP };
    std::string title;
    std::vector<size_t> leftList, rightList;

    void splitList(const vector<string> &inputList);
    size_t solveTwoStarProblem(const SolutionDataStructure &dataStructure);
    size_t twoStarsMap();
    size_t twoStarsPreSortedLists();
    size_t twoStarsUnorderedMap();
public:
    explicit Day1Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day1Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day1Solution>(puzzleInput);
    }
};

#endif //DAY1SOLUTION_H
