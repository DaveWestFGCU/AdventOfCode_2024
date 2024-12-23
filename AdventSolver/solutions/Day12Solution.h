/** Dev: Dave West
 * Date: December 12, 2024
 * Desc: Class declarations for the AoC 2024 day 12 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY12SOLUTION_H
#define DAY12SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include "data_structures/Grid.h"
#include <vector>
#include <string>


class Day12Solution : public Solution {
    string title;
    Grid plotMap;

        // One-Star Methods


public:
    explicit Day12Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day12Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day12Solution>(puzzleInput);
    }
};



#endif //DAY12SOLUTION_H
