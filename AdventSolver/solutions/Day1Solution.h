/*  Dev: Dave West
 * Date: December 1, 2024
 * Desc: Class declarations for the AoC 2024 day 1 puzzle solution and solution factory.
 */

#ifndef DAY1SOLUTION_H
#define DAY1SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using std::vector, std::string;

class Day1Solution : public Solution {
    enum twoStarSolution {sortedList, map, unordered_map};
    std::string title;
    std::vector<size_t> leftList, rightList;

    void splitList(const vector<string> & inputList);
    size_t twoStarsMap();
    size_t twoStarsPreSortedLists();
    size_t twoStarsUnorderedMap();
public:
    Day1Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override;
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day1Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day1Solution>(puzzleInput);
    }
};

#endif //DAY1SOLUTION_H
