

#ifndef DAY2SOLUTION_H
#define DAY2SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>

using std::vector, std::string;

class Day2Solution : public Solution {
    string title;
    vector<vector<int>>reports;

    vector<vector<int>> parseStringToIntegers(const vector<string> & input);
    bool levelsAreSafe(vector<int> levels);
    bool trendIsSafe(const vector<int> & levels);
    bool changeIsSafe(const vector<int> & levels);

public:
    Day2Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day2Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day2Solution>(puzzleInput);
    }
};

#endif //DAY2SOLUTION_H
