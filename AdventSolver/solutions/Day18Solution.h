/** Dev: Dave West
 * Date: December 18, 2024
 * Desc: Class declarations for the AoC 2024 day 18 puzzle solution and solution factory.
**/

#ifndef DAY18SOLUTION_H
#define DAY18SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day18Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day18Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day18Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day18Solution>(puzzleInput);
    }
};



#endif //DAY18SOLUTION_H
