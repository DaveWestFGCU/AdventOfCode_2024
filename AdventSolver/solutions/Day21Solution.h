/** Dev: Dave West
 * Date: December 21, 2024
 * Desc: Class declarations for the AoC 2024 day 21 puzzle solution and solution factory.
 */

#ifndef DAY21SOLUTION_H
#define DAY21SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map, std::pair;

class Day21Solution : public Solution {
    string title;
    struct Position { int x, y; };
    enum Button { A = 10 };
    enum Direction { LEFT, DOWN, RIGHT, UP, ACT };
    vector<string> doorCodes;

    struct IntIntPairHash
    {
        size_t operator()(const pair<int,int> &intPair) const
        { return std::hash<int>()(intPair.first) ^ (std::hash<int>()(intPair.second) << 1); }
    };
    unordered_map<pair<int,int>,string,IntIntPairHash> numKeyLookup;

    struct CharCharPairHash
    {
        size_t operator()(const pair<char,char> &charPair) const
        { return std::hash<char>()(charPair.first) ^ (std::hash<char>()(charPair.second) << 1); }
    };
    unordered_map<pair<char,char>,string,CharCharPairHash> directionLookup;

    struct CharPairIntPairHash
    {
        size_t operator()(const pair<pair<char,char>,int> &CharPairIntPair) const
        { return CharCharPairHash()(CharPairIntPair.first) ^ (std::hash<int>()(CharPairIntPair.second) << 1); }
    };
    unordered_map<pair<pair<char,char>,int>,long long,CharPairIntPairHash> cache;

        // Construct lookups
    void buildNumberToDirectionLookup();
    string numKeysToDirectionKeys(Position button1, Position button2);
    void buildDirectionToDirectionLookup();
    string directionKeysToDirectionKeys(Position fromKey, Position toKey);

    string codeToDirections(const string &code);
    long long translateDirectionToDirections(const char &fromKey, const char &toKey, const int &depth);

public:
    explicit Day21Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day21Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day21Solution>(puzzleInput);
    }
};


#endif //DAY21SOLUTION_H
