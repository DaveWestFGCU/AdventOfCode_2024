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
        initialStones.push_back(value);
}


std::pair<long long,long long> Day11Solution::blink(const long long &stoneValue)
{
    if (stoneValue == 0)
        return {1, -1};

    string stoneString = std::to_string(stoneValue);
    if (stoneString.length() % 2 == 0)
    {
        int halfDigits = stoneString.length() / 2;
        return {std::stoll(stoneString.substr(0,halfDigits)), std::stoll(stoneString.substr(halfDigits,halfDigits))};
    }

    return {stoneValue * 2024, -1};
}


long long Day11Solution::stonesPerBlink(long long stoneValue, int depth)
{
    // Base case: No more blinks
    if (depth == 0)
        return 1;

    // Use cache if value/depth has been seen before
    if (cache.contains(stoneValue))
        if (cache[stoneValue][depth] != 0)
            return cache[stoneValue][depth];

    // Get values for this stone
    auto [leftStone, rightStone] = blink(stoneValue);

    long long output = stonesPerBlink(leftStone, depth - 1);
    if (rightStone != -1)
        output += stonesPerBlink(rightStone, depth - 1);

    // Add to cache now that number of stones for this depth is known.
    cache[stoneValue][depth] = output;
    return output;
}


string Day11Solution::oneStarSolution()
{
    int totalStones = 0;

    for (const auto &stone : initialStones)
        totalStones += stonesPerBlink(stone, 25);

    return std::to_string(totalStones);
}


string Day11Solution::twoStarSolution()
{
    long long totalStones = 0;

    for (const auto &stone : initialStones)
        totalStones += stonesPerBlink(stone, 75);

    return std::to_string(totalStones);
}
