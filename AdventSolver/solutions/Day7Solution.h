/*  Dev: Dave West
 * Date: December 7, 2024
 * Desc: Class declarations for the AoC 2024 day 7 puzzle solution and solution factory.
 */

#ifndef DAY7SOLUTION_H
#define DAY7SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <unordered_map>
#include <sstream>

using std::vector, std::string;

class Day7Solution : public Solution {
    string title;
    std::unordered_map<size_t,vector<size_t>> calibrations;

    void addCalibrations(const vector<string>& puzzleInput);
public:
        // Setup methods
    explicit Day7Solution(const std::vector<std::string> & puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }


        // One-star solution methods
    int oneStarSolution() override;
    bool equationSolutionExists(const size_t& result, const vector<size_t>& numbers);
    size_t add(const size_t& result, const vector<size_t>& numbers, size_t index, size_t currentResult, bool& bottomReached);
    size_t multiply(const size_t& result, const vector<size_t>& numbers, size_t index, size_t currentResult, bool& bottomReached);

        // Two-star solution methods
    int twoStarSolution() override;
};


class Day7Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day7Solution>(puzzleInput);
    }
};



#endif //DAY7SOLUTION_H
