/*  Dev: Dave West
 * Date: December 2, 2024
 * Desc: Method definitions for the AoC 2024 day 2 puzzle.
 *  Log: 12/2/2024 - Completed solution.
 *       12/4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/7/2024 - Refactored ints to long long or size_t.
 *                   Refactored puzzle parsing to stringstream.
 */

#include "Day2Solution.h"


Day2Solution::Day2Solution(const std::vector<std::string> & puzzleInput) {
    title = "--- Day 2: Red-Nosed Reports ---";
    reports = parseStringToIntegers(puzzleInput);
}


vector<vector<size_t>> Day2Solution::parseStringToIntegers(const vector<string> & input)
{
    vector<vector<size_t>> reports;

    for (const auto& line : input)
    {
        vector<size_t> levels;
        std::stringstream ss(line);

        size_t number;
        while(ss >> number)
            levels.push_back(number);
    }

    return reports;
}


long long Day2Solution::oneStarSolution() {
    int safeCount {0};
    for (const auto & levels : reports)
    {
        // Unsafe: Reactor is not maintaining trend
        if (!trendIsSafe(levels))
            continue;

        // Unsafe: Reactor increasing or decreasing too quickly
        if (!changeIsSafe(levels))
            continue;

        // If code reaches here, the report is safe.
        safeCount++;
    }

    return safeCount;
}


bool Day2Solution::trendIsSafe(const vector<size_t> & levels)
{
    for (int i = 0; i < levels.size()-2; i++)
    {
        if (levels[i] == levels[i+1] || levels[i+1] == levels[i+2])
            return false;

        if (levels[i] < levels[i+1])
            if (levels[i+1] > levels[i+2])
                return false;

        if (levels[i] > levels[i+1])
            if (levels[i+1] < levels[i+2])
                return false;
    }

    return true;
}


bool Day2Solution::changeIsSafe(const vector<size_t> & levels)
{
    for (int i = 0; i < levels.size()-1; i++)
    {
        int difference = static_cast<int>(levels[i+1]) - static_cast<int>(levels[i]);
        if (difference > 3 || difference < -3)
        {   // Unsafe: Reactor increasing or decreasing too quickly
            return false;
        }
    }

    return true;
}


long long Day2Solution::twoStarSolution() {
    int safeCount {0};
    for (const auto & levels : reports)
    {
        if (levelsAreSafe(levels))
        {
            safeCount++;
            continue;
        }

        // Check if safe with problem dampening
        for (int i = 0; i < levels.size(); i++)
        {
            vector<size_t> dampenedLevels = levels;
            dampenedLevels.erase(dampenedLevels.begin()+i);
            if (levelsAreSafe(dampenedLevels))
            {
                safeCount++;
                break;
            }
        }

    } // end report loop

    return safeCount;
}


bool Day2Solution::levelsAreSafe(vector<size_t> levels)
{
    // Unsafe: Reactor is not maintaining trend
    if (!trendIsSafe(levels))
        return false;

    // Unsafe: Reactor increasing or decreasing too quickly
    if (!changeIsSafe(levels))
        return false;

    return true;
}
