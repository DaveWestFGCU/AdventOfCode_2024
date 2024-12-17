/** Dev: Dave West
 * Date: December 17, 2024
 * Desc: Class declarations for the AoC 2024 day 17 puzzle solution and solution factory.
**/

#ifndef DAY17SOLUTION_H
#define DAY17SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Day17Solution : public Solution {
    string title;
    vector<string> puzzleInput;

public:
    explicit Day17Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day17Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day17Solution>(puzzleInput);
    }
};



#endif //DAY17SOLUTION_H
