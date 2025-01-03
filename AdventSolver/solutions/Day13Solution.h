/** Dev: Dave West
 * Date: December 13, 2024
 * Desc: Class declarations for the AoC 2024 day 13 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY13SOLUTION_H
#define DAY13SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <regex>


class Day13Solution : public Solution {
    string title;
    class ClawGame
    {
        struct Pos { long long x, y; } buttonA, buttonB, prize;
        long long aPresses, bPresses;
        size_t tokensPerAPress, tokensPerBPress;
        size_t costToWin;

        void applyCramersRule();
        void calculateWinCost();
    public:
        ClawGame(const std::pair<size_t,size_t> &buttonA, const std::pair<size_t,size_t> &buttonB, const std::pair<size_t,size_t> &prize);

            // Setter
        void recalibrate(const long long &addend);

            // Getters
        [[nodiscard]] bool isWinnable() const { return costToWin > 0; }
        [[nodiscard]] size_t winCost() const { return costToWin; }
    };
    vector<ClawGame> clawGames;

    void parseClawGames(const vector<string> &puzzleInput);
    std::pair<size_t,size_t> parseValues(string line);

public:
    explicit Day13Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day13Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day13Solution>(puzzleInput);
    }
};



#endif //DAY13SOLUTION_H
