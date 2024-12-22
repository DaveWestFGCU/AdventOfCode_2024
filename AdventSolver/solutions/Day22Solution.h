/** Dev: Dave West
 * Date: December 22, 2024
 * Desc: Class declarations for the AoC 2024 day 22 puzzle solution and solution factory.
 */

#ifndef DAY22SOLUTION_H
#define DAY22SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day22Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day22Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day22Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day22Solution>(puzzleInput);
    }
};


#endif //DAY22SOLUTION_H
