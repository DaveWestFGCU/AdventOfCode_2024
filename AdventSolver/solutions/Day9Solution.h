/*  Dev: Dave West
 * Date: December 9, 2024
 * Desc: Class declarations for the AoC 2024 day 9 puzzle solution and solution factory.
 */

#ifndef DAY9SOLUTION_H
#define DAY9SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day9Solution : public Solution {
    string title;
    string diskMap;

public:
    explicit Day9Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day9Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day9Solution>(puzzleInput);
    }
};



#endif //DAY9SOLUTION_H
