/*  Dev: Dave West
 * Date: December 11, 2024
 * Desc: Class declarations for the AoC 2024 day 11 puzzle solution and solution factory.
 */

#ifndef DAY11SOLUTION_H
#define DAY11SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day11Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day11Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day11Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day11Solution>(puzzleInput);
    }
};



#endif //DAY11SOLUTION_H
