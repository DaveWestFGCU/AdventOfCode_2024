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
#include <unordered_set>

using std::vector, std::string;

class Day8Solution : public Solution {
    class Pos
    {
    public:
        int y,x;
        Pos(int y, int x) : y(y), x(x) {};
        bool operator==(const Pos &position2) const {   // Unordered sets disallow duplicates
            return x == position2.x && y == position2.y;
        }
        inline bool isAbove(  const Pos &position) const { return y < position.y; }
        inline bool isBelow(  const Pos &position) const { return y > position.y; }
        inline bool isLeftOf( const Pos &position) const { return x < position.x; }
        inline bool isRightOf(const Pos &position) const { return x > position.x; }
    };
    struct PosHash  // Hash function for unordered set
    {
        size_t operator()(const Pos &pos) const
        {
            const size_t yHash = std::hash<size_t>{}(pos.y);
            const size_t xHash = std::hash<size_t>{}(pos.x);

            return yHash ^ (xHash << 1);
        }
    };
    string title;
    Pos mapBounds;
    std::unordered_map<char,vector<Pos>> frequencyToAntennaLocations;   //  Organize nodes by frequency
    std::unordered_set<Pos,PosHash> antinodeLocations;  //  Don't want duplicates, don't care about sorting

        // Setup
    void buildAntennaPositionLists(const vector<string> &puzzleInput);
    void printFrequencies();


        // One Star Methods
    void findAntinodes(const vector<Pos> &antennaLocations);
    bool isInBounds(Pos antinodePosition) const;

        // Two Star Methods
public:
    explicit Day8Solution(const vector<string> &puzzleInput);
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
