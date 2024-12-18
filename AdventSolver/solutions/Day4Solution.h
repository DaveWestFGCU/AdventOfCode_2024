/** Dev: Dave West
 * Date: December 4, 2024
 * Desc: Class declarations for the AoC 2024 day 4 puzzle solution and solution factory.
 *  Log: 12/ 4/2024 - Completed solution.
 *       12/ 7/2024 - Refactored ints to long long or size_t.
 *       12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY4SOLUTION_H
#define DAY4SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <regex>

class Day4Solution : public Solution {
    string title;
    vector<string> puzzleInput;

    size_t countHorizontal(const std::regex & pattern);          //  -
    size_t countVertical(const std::regex & pattern);            //  |
    size_t countForwardDiagonal(const std::regex & pattern);     //  /
    size_t countBackwardDiagonal(const std::regex & pattern);    //  \

    bool isXmas(const size_t & row, const size_t & col);

public:
    explicit Day4Solution(const std::vector<std::string> & puzzleInput);
    [[nodiscard]] string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day4Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day4Solution>(puzzleInput);
    }
};

#endif //DAY4SOLUTION_H
