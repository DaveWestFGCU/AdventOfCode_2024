/** Dev: Dave West
 * Date: December 23, 2024
 * Desc: Class declarations for the AoC 2024 day 23 puzzle solution and solution factory.
 */

#ifndef DAY23SOLUTION_H
#define DAY23SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <set>

using std::unordered_map, std::tuple, std::set;

class Day23Solution : public Solution {
    string title;
    struct Computer
    {
        unordered_map<string,Computer*>connections;
    };
    unordered_map<string, Computer> lanConnections;
    set<tuple<string,string,string>> connectionTriplets;

    void parseLanConnections(const vector<string> &puzzleInput);
    static vector<string> split(const string &stringToParse, const char &delimiter);

    void findConnectionTriplets();

    vector<string> findMaximalClique();
    vector<string> _findMaximalClique(vector<string> currentClique, const string &nextComputer);

public:
    explicit Day23Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day23Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day23Solution>(puzzleInput);
    }
};


#endif //DAY23SOLUTION_H
