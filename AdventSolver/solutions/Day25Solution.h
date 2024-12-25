/** Dev: Dave West
 * Date: December 25, 2024
 * Desc: Class declarations for the AoC 2024 day 25 puzzle solution and solution factory.
 */

#ifndef DAY25SOLUTION_H
#define DAY25SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day25Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day25Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day25Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day25Solution>(puzzleInput);
    }
};


#endif //DAY25SOLUTION_H
