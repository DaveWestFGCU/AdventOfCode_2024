/*  Dev: Dave West
 * Date: December 5, 2024
 * Desc: Class declarations for the AoC 2024 day 5 puzzle solution and solution factory.
 */

#ifndef DAY5SOLUTION_H
#define DAY5SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <algorithm>

using std::vector, std::string;

class Day5Solution : public Solution {
    string title;
    struct PageRule { size_t before, after; };  // Ordered pair from the ordering page rules. before is a page that comes before after.
    vector<int> beforeList[100];                // Page numbers coming before the number at the index.
    vector<int> afterList[100];                 // Page numbers coming after the number at the index.
    vector<vector<int>> updates;                // Pages in an update.

    // Input Parsing
    void parsePuzzleInput(const vector<string> & puzzleInput);
    PageRule parsePageOrderingRule(const std::string & unparsedPageRule);
    vector<int> parseUpdate(const std::string & unparsedUpdate);
    bool isDigit(const char & character);

    // Used in One-Star Solution
    bool isUpdateInOrder(vector<int> update);

    // Used in Two-Star Solution
    vector<int> reorderUpdate(const vector<int> & update);
    
public:
    explicit Day5Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override { return title; }
    int oneStarSolution() override;
    int twoStarSolution() override;
};


/**
 * Creator class for the day 5 solution.
 */
class Day5Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day5Solution>(puzzleInput);
    }
};

#endif //DAY5SOLUTION_H
