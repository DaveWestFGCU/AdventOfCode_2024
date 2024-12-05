

#ifndef DAY5SOLUTION_H
#define DAY5SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>

using std::vector, std::string;

class Day5Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    Day5Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day5Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day5Solution>(puzzleInput);
    }
};

#endif //DAY5SOLUTION_H
