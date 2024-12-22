/** Dev: Dave West
 * Date: December 22, 2024
 * Desc: Class declarations for the AoC 2024 day 22 puzzle solution and solution factory.
 */

#ifndef DAY22SOLUTION_H
#define DAY22SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;

class Day22Solution : public Solution {
    string title;
    vector<int> secretNumbers;

    struct SellSequence
    {
        short one, two, three, four;
        SellSequence()
            : one(0), two(0), three(0), four(0) {}
        explicit SellSequence(const short &one)
            : one(one), two(0), three(0), four(0) {}
        SellSequence(const short &one, const SellSequence &seq)
            : one(one), two(seq.one), three(seq.two), four(seq.three) {}
        SellSequence(const short &one, const short &two, const short &three, const short &four)
            :one(one), two(two), three(three), four(four) {}
        bool operator==(const SellSequence &otherSeq) const
        {
            return one == otherSeq.one && two == otherSeq.two && three == otherSeq.three && four == otherSeq.four;
        }
    };

    struct SellSequencesHash
    {
        size_t operator()(const SellSequence &seq) const
        {
            const size_t oneHash = std::hash<short>()(seq.one);
            const size_t twoHash = std::hash<short>()(seq.two);
            const size_t threeHash = std::hash<short>()(seq.three);
            const size_t fourHash = std::hash<short>()(seq.four);
            return oneHash ^ (twoHash << 1) ^ (threeHash << 2) ^ (fourHash << 3);
        }
    };

    struct SellSequenceValues
    {
        bool seen;
        int totalBananas;
        SellSequenceValues() : seen(false), totalBananas(0) {}
    };
    unordered_map<SellSequence,SellSequenceValues,SellSequencesHash> sellSequences;

    int findNextSecretNumber(int secretNumber);
    int secretNumberEvolutionStep1(const int &secretNumber);
    int secretNumberEvolutionStep2(const int &secretNumber);
    int secretNumberEvolutionStep3(const int &secretNumber);

    void findSellSequenceBananaCounts();

public:
    explicit Day22Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day22Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day22Solution>(puzzleInput);
    }
};


#endif //DAY22SOLUTION_H
