/** Dev: Dave West
 * Date: December 11, 2024
 * Desc: Method definitions for the AoC 2024 day 11 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#include "Day11Solution.h"


Day11Solution::Day11Solution(const vector<string> &puzzleInput)
    : title("--- Day 11: Plutonian Pebbles ---")
{
    getInitialStones(puzzleInput);
}


void Day11Solution::getInitialStones(const vector<string> &puzzleInput)
{
    std::stringstream ss(puzzleInput[0]);
    int value;

    while (ss >> value)
        initialStones.push_back(std::to_string(value));
}


string Day11Solution::oneStarSolution()
{
    int totalBlinks = 25;

    for (const auto &stone : initialStones)
        scoreStone(stone, totalBlinks);

    uint64_t totalStones {0};
    for (auto stone : initialStones)
        totalStones += stoneScores[stone][totalBlinks];

    return std::to_string(totalStones);
}


unsigned long Day11Solution::scoreStone(string stone, int blink)
{   std::cout << stone << " | ";
    if(stoneScores[stone][blink] != 0)
        return stoneScores[stone][blink];

    if (blink == 0)
    {
        stoneScores[stone][blink] = 1;
        return 1;
    }

    unsigned long totalScore {0};
        //  If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
    if (stone == "0")
        totalScore = scoreStone("1", blink-1);

        //  If the stone is engraved with a number that has an even number of digits, it is replaced by two stones.
        //  The left half of the digits are engraved on the new left stone, and the right half of the digits are
        //  engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become
        //  stones 10 and 0.)
    else if (stone.length() % 2 == 0)
    {
        int halfDigits = stone.length() / 2;
        totalScore = scoreStone(stone.substr(0, halfDigits), blink-1);
        totalScore += scoreStone(stone.substr(halfDigits+1, halfDigits), blink-1);
    }

        //  If none of the other rules apply, the stone is replaced by a new stone; the old stone's number
        //  multiplied by 2024 is engraved on the new stone.
    else
    {
        string newStone = std::to_string(std::stoi(stone) * 2024);
        std::cout << stone << " -> " << newStone << " | ";
        totalScore = scoreStone(newStone, blink-1);
    }

    stoneScores[stone][blink] = totalScore;

    return totalScore;
}


string Day11Solution::twoStarSolution()
{
    int result {0};

    return std::to_string(result);
}
