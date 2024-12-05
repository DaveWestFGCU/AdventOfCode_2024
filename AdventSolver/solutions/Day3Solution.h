

#ifndef DAY3SOLUTION_H
#define DAY3SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <regex>

using std::vector, std::string;

class Day3Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    Day3Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day3Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day3Solution>(puzzleInput);
    }
};

#endif //DAY3SOLUTION_H
