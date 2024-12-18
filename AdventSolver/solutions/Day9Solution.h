/** Dev: Dave West
 * Date: December 9, 2024
 * Desc: Class declarations for the AoC 2024 day 9 puzzle solution and solution factory.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#ifndef DAY9SOLUTION_H
#define DAY9SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <queue>
#include <stack>

using std::vector, std::string;

class Day9Solution : public Solution {
    struct Block { size_t expandedLoc, size, fileId; };
    string title;
    vector<size_t> diskMap;
    vector<int> expandedDiskMap;    //  int: free space represented by -1
    std::stack<Block> files;        //  Part 2, files need to be accessed from back to front (FILO)
    vector<Block> freeSpaces;   //  Part 2, free space needs to be accessed from front to back and searchable

    void partitionDiskMap();

    static inline bool blockIsFile(size_t loc);
    void expandDiskMap();
    void printExpandedDiskMap() const;

        //  One-star solution methods
    void fragmentedCompaction();

        //  Two-star solution methods
    void contiguousCompaction();

public:
    explicit Day9Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day9Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day9Solution>(puzzleInput);
    }
};



#endif //DAY9SOLUTION_H
