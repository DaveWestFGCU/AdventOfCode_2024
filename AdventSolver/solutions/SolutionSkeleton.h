/*  Dev: Dave West
 * Date: December $, 2024
 * Desc: Method definitions for the AoC 2024 day $ puzzle.
 */

#ifndef DAY$SOLUTION_H
#define DAY$SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include<vector>
#include<string>

using std::vector, std::string;

class Day$Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day$Solution(const std::vector<std::string> & puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day$Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day$Solution>(puzzleInput);
    }
};



#endif //DAY$SOLUTION_H
