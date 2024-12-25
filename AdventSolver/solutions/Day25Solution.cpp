/** Dev: Dave West
 * Date: December 25, 2024
 * Desc: Method definitions for the AoC 2024 day 25 puzzle.
 */

#include "Day25Solution.h"


Day25Solution::Day25Solution(const vector<string> &puzzleInput)
    : title("--- Day 25: Code Chronicle ---")
{
    parseKeysAndLocks(puzzleInput);
}


void Day25Solution::parseKeysAndLocks(const vector<string> &puzzleInput)
{
    for (int i = 0; i < puzzleInput.size(); i+=8)
    {
        if (puzzleInput[i][0] == '#')
            parseLock(puzzleInput, i);

        else
            parseKey(puzzleInput, i);
    }
}


void Day25Solution::parseKey(const vector<string> &puzzleInput, const int &startIndex)
{
    int pin[5] {0,0,0,0,0};
    for(int y = startIndex+1; y < startIndex+6; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            if (puzzleInput[y][x] == '#')
                ++pin[x];
        }
    }

    keys.emplace_back(pin);
}


void Day25Solution::parseLock(const vector<string> &puzzleInput, const int &startIndex)
{
    int pin[5] {0,0,0,0,0};
    for(int y = startIndex+1; y < startIndex+6; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            if (puzzleInput[y][x] == '#')
                ++pin[x];
        }
    }

    locks.emplace_back(pin);
}


string Day25Solution::oneStarSolution()
{
    int keyLockPairCount { 0 };

    for (const Key &key : keys)
        for (const Lock &lock : locks)
            if (tryKeyInLock(key, lock))
                ++keyLockPairCount;

    return std::to_string(keyLockPairCount);
}


bool Day25Solution::tryKeyInLock(const Key &key, const Lock &lock)
{
    for (int pindex = 0; pindex < 5; ++pindex)
    {
        if (key.pin[pindex] + lock.pin[pindex] > 5)
            return false;
    }

    return true;
}


string Day25Solution::twoStarSolution()
{
    int result {0};

    return std::to_string(result);
}
