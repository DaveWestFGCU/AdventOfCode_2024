/** Dev: Dave West
 * Date: December 21, 2024
 * Desc: Class declarations for the AoC 2024 day 21 puzzle solution and solution factory.
 */

#ifndef DAY21SOLUTION_H
#define DAY21SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day21Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day21Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day21Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day21Solution>(puzzleInput);
    }
};


#endif //DAY21SOLUTION_H
