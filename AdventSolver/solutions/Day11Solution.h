/** Dev: Dave West
 * Date: December 11, 2024
 * Desc: Class declarations for the AoC 2024 day 11 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY11SOLUTION_H
#define DAY11SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>
#include <cmath>


class Day11Solution : public Solution {
    string title;
    vector<string> initialStones;
    std::unordered_map<string, long[75]> stoneScores;
        // Constructor methods
    void getInitialStones(const vector<string> &puzzleInput);

        // One-star methods
    unsigned long scoreStone(string stone, int blink);

public:
    explicit Day11Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day11Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day11Solution>(puzzleInput);
    }
};



#endif //DAY11SOLUTION_H
