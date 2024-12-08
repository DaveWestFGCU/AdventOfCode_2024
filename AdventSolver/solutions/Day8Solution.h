/*  Dev: Dave West
 * Date: December 8, 2024
 * Desc: Class declarations for the AoC 2024 day 8 puzzle solution and solution factory.
 */

#ifndef DAY8SOLUTION_H
#define DAY8SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <unordered_map>

using std::vector, std::string;

class Day8Solution : public Solution {
    struct Pos {size_t y,x;};
    string title;
    std::unordered_map<char,vector<Pos>> frequencyLocations;

        // Setup
    void buildAntennaPositionLists(const vector<string>& puzzleInput);
    void printFrequencies();


        // One Star Methods


        // Two Star Methods
public:
    explicit Day8Solution(const vector<string>& puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day8Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day8Solution>(puzzleInput);
    }
};



#endif //DAY8SOLUTION_H
