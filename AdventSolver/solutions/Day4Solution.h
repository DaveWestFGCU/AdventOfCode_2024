

#ifndef DAY4SOLUTION_H
#define DAY4SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <regex>

using std::vector, std::string;

class Day4Solution : public Solution {
    string title;
    vector<string> puzzleInput;

    size_t countHorizontal(const std::regex & pattern);          //  -
    size_t countVertical(const std::regex & pattern);            //  |
    size_t countForwardDiagonal(const std::regex & pattern);     //  /
    size_t countBackwardDiagonal(const std::regex & pattern);    //  \

    bool isXmas(const size_t & row, const size_t & col);

public:
    Day4Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day4Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day4Solution>(puzzleInput);
    }
};

#endif //DAY4SOLUTION_H
