/*  Dev: Dave West
 * Date: December 7, 2024
 * Desc: Class declarations for the AoC 2024 day 7 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY7SOLUTION_H
#define DAY7SOLUTION_H


#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <sstream>
#include <cmath>

class Day7Solution : public Solution {
    string title;
    vector<std::pair<size_t,vector<size_t>>> calibrations;
    enum Feature {ON, OFF};

    void addCalibrations(const vector<string>& puzzleInput);
    bool equationSolutionExists(const size_t& result,
                                const vector<size_t>& numbers,
                                size_t currentResult,
                                size_t index,
                                Feature concatenation = OFF);
    static short getDigits(size_t number);
    static inline size_t concatenate(const size_t& num1, const size_t& num2);

        // Optimized implementation: Left-to-Right
    bool reverseEqnSlnExists(const size_t& result,
                             const vector<size_t>& numbers,
                             long long currentResult,
                             size_t index,
                             Feature concatenation = OFF);
public:
        // Setup methods
    explicit Day7Solution(const std::vector<std::string> & puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }

        // Solutions
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day7Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day7Solution>(puzzleInput);
    }
};



#endif //DAY7SOLUTION_H
