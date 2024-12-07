

#ifndef DAY7SOLUTION_H
#define DAY7SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <regex>

using std::vector, std::string;

class Day7Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day7Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day7Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day7Solution>(puzzleInput);
    }
};

#endif //DAY7SOLUTION_H
