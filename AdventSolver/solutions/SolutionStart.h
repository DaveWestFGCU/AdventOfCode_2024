/** Dev: Dave West
 * Date: December $, 2024
 * Desc: Class declarations for the AoC 2024 day $ puzzle solution and solution factory.
**/

#ifndef DAY$SOLUTION_H
#define DAY$SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day$Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day$Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day$Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day$Solution>(puzzleInput);
    }
};


#endif //DAY$SOLUTION_H
