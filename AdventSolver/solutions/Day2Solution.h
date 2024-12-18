/** Dev: Dave West
 * Date: December 2, 2024
 * Desc: Class declarations for the AoC 2024 day 2 puzzle solution and solution factory.
 *  Log: 12/ 2/2024 - Completed solution.
 *       12/ 4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/ 7/2024 - Refactored ints to long long or size_t.
 *                    Refactored puzzle parsing to stringstream.
 *       12/17/2024 - Refactored one and two star solutions to return strings.
 */

#ifndef DAY2SOLUTION_H
#define DAY2SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <sstream>

class Day2Solution : public Solution {
    string title;
    vector<vector<size_t>>reports;

    vector<vector<size_t>> parseStringToIntegers(const vector<string> & puzzleInput);
    bool levelsAreSafe(const vector<size_t>& levels);
    bool trendIsSafe(const vector<size_t> & levels);
    bool changeIsSafe(const vector<size_t> & levels);

public:
    explicit Day2Solution(const vector<string> & puzzleInput);
    [[nodiscard]] string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day2Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day2Solution>(puzzleInput);
    }
};

#endif //DAY2SOLUTION_H
