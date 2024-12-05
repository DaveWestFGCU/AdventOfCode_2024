

#ifndef DAY1SOLUTION_H
#define DAY1SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <regex>
#include <vector>
#include <unordered_map>

using std::vector, std::string;

class Day1Solution : public Solution {
    enum twoStarSolution {sortedList, map, unordered_map};
    std::string title;
    std::vector<int> leftList, rightList;

    void splitList(const vector<string> & inputList, vector<int> & leftList, vector<int> & rightList);
    int twoStarsMap(const vector<int> & leftList, const vector<int> & rightList);
    int twoStarsPreSortedLists(const vector<int> & leftList, const vector<int> & rightList);
    int twoStarsUnorderedMap(const vector<int> & leftList, const vector<int> & rightList);
public:
    Day1Solution(const std::vector<std::string> & puzzleInput);
    std::string getTitle() const override;
    int oneStarSolution() override;
    int twoStarSolution() override;
};


class Day1Creator : public AdventSolver {
public:
    std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day1Solution>(puzzleInput);
    }
};

#endif //DAY1SOLUTION_H
