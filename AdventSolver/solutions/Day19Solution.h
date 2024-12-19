/** Dev: Dave West
* Date: December 19, 2024
 * Desc: Class declarations for the AoC 2024 day 19 puzzle solution and solution factory.
 */

#ifndef DAY19SOLUTION_H
#define DAY19SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <unordered_map>


class Day19Solution : public Solution {
    string title;

    vector<string> towelPatterns;
    vector<string> designs;
    std::unordered_map<string,long long> possibilityCounts;

    void printTowels();
    bool isPossible(const string &design);
    void sortPatterns();
    string findNextTowel(string design);

    long long countPossibilities(const string &design);

public:
    explicit Day19Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day19Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day19Solution>(puzzleInput);
    }
};


#endif //DAY19SOLUTION_H
