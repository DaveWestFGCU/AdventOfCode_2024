/** Dev: Dave West
 * Date: December 25, 2024
 * Desc: Class declarations for the AoC 2024 day 25 puzzle solution and solution factory.
 *  Log: 12/25/24 - Completed one-star solution. Two-star requires obtaining all 49 prior stars.
 *       12/28/24 - Completed two-star solution! 50/50 stars obtained!
 */

#ifndef DAY25SOLUTION_H
#define DAY25SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>


class Day25Solution : public Solution {
    string title;

    struct Key
    {
        int pin[5];
        explicit Key(int pin[5]) : pin{pin[0],pin[1],pin[2],pin[3],pin[4]} {}
    };
    struct Lock
    {
        int pin[5];
        explicit Lock(int pin[5]) : pin{pin[0],pin[1],pin[2],pin[3],pin[4]} {}
    };
    vector<Key> keys;
    vector<Lock> locks;

    void parseKeysAndLocks(const vector<string> &puzzleInput);
    void parseKey(const vector<string> &puzzleInput, const int &startIndex);
    void parseLock(const vector<string> &puzzleInput, const int &startIndex);

    static bool tryKeyInLock(const Key &key, const Lock &lock);

public:
    explicit Day25Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day25Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day25Solution>(puzzleInput);
    }
};


#endif //DAY25SOLUTION_H
