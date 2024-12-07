/*  Dev: Dave West
 * Date: December 1, 2024
 * Desc: Class declarations for the AoC 2024 day 1 puzzle solution and solution factory.
 *  Log: 12/2/2024 - Completed solution.
 *       12/4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/7/2024 - Refactored ints to long long or size_t.
 *                   Refactored puzzle parsing to stringstream.
 */

#ifndef DAY2SOLUTION_H
#define DAY2SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <sstream>

using std::vector, std::string;

class Day2Solution : public Solution {
    string title;
    vector<vector<size_t>>reports;

    vector<vector<size_t>> parseStringToIntegers(const vector<string> & puzzleInput);
    bool levelsAreSafe(vector<size_t> levels);
    bool trendIsSafe(const vector<size_t> & levels);
    bool changeIsSafe(const vector<size_t> & levels);

public:
    Day2Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day2Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day2Solution>(puzzleInput);
    }
};

#endif //DAY2SOLUTION_H
