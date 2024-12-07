/*  Dev: Dave West
 * Date: December 3, 2024
 * Desc: Class declarations for the AoC 2024 day 3 puzzle solution and solution factory.
 *  Log: 12/3/24 - Completed solution.
 *       12/4/24 - Refactored from its own program to a class for a larger solutions program.
 *       12/7/24 - Refactored ints to long long or size_t.
 */

#ifndef DAY3SOLUTION_H
#define DAY3SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <regex>

using std::vector, std::string;

class Day3Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    Day3Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day3Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day3Solution>(puzzleInput);
    }
};

#endif //DAY3SOLUTION_H
