/*  Dev: Dave West
* Date: December 15, 2024
 * Desc: Class declarations for the AoC 2024 day 15 puzzle solution and solution factory.
 */

#ifndef DAY15SOLUTION_H
#define DAY15SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day15Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day15Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day15Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day15Solution>(puzzleInput);
    }
};



#endif //DAY15SOLUTION_H
