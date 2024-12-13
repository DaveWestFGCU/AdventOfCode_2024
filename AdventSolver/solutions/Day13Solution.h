/*  Dev: Dave West
* Date: December 13, 2024
 * Desc: Class declarations for the AoC 2024 day 13 puzzle solution and solution factory.
 */

#ifndef DAY13SOLUTION_H
#define DAY13SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day13Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day13Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day13Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day13Solution>(puzzleInput);
    }
};



#endif //DAY13SOLUTION_H