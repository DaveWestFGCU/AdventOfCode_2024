/** Dev: Dave West
* Date: December 20, 2024
 * Desc: Class declarations for the AoC 2024 day 20 puzzle solution and solution factory.
 */

#ifndef DAY20SOLUTION_H
#define DAY20SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day20Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day20Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day20Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day20Solution>(puzzleInput);
    }
};


#endif //DAY20SOLUTION_H
