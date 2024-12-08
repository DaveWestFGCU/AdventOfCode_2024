/*  Dev: Dave West
 * Date: December 8, 2024
 * Desc: Class declarations for the AoC 2024 day 8 puzzle solution and solution factory.
 */

#ifndef DAY8SOLUTION_H
#define DAY8SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day8Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day8Solution(const std::vector<std::string> & puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day8Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day8Solution>(puzzleInput);
    }
};



#endif //DAY8SOLUTION_H
