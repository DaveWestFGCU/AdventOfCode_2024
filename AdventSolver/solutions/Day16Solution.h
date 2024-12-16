/**  Dev: Dave West
 * Date: December 16, 2024
 * Desc: Class declarations for the AoC 2024 day 16 puzzle solution and solution factory.
**/

#ifndef DAY16SOLUTION_H
#define DAY16SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day16Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day16Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day16Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day16Solution>(puzzleInput);
    }
};



#endif //DAY16SOLUTION_H
