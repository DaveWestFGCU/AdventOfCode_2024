/** Dev: Dave West
 * Date: December 24, 2024
 * Desc: Class declarations for the AoC 2024 Christmas Eve puzzle solution and solution factory.
 */

#ifndef DAY24SOLUTION_H
#define DAY24SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day24Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day24Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day24Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day24Solution>(puzzleInput);
    }
};


#endif //DAY24SOLUTION_H
