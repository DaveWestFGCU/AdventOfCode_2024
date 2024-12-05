

#include "Day2Solution.h"


Day2Solution::Day2Solution(std::vector<std::string> puzzleInput) {
    title = "--- Day 2: Red-Nosed Reports ---";
    reports = parseStringToIntegers(puzzleInput);
}

vector<vector<int>> Day2Solution::parseStringToIntegers(const vector<string> & input)
{
    vector<vector<int>> reports;
    for (auto level : input)
    {
        vector<int> levels;
        int num = 0;
        for (int i = 0; i < level.length(); i++)
        {
            if (level[i] != ' ')
                num = num * 10 + (level[i]-'0');

            if (level[i] == ' ' || i == level.length()-1)
            {
                levels.push_back(num);
                num = 0;
            }
        }

        reports.push_back(levels);
    }

    return reports;
}


int Day2Solution::oneStarSolution(std::vector<std::string> puzzleInput) {
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


bool Day2Solution::trendIsSafe(const vector<int> & levels)
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


bool Day2Solution::changeIsSafe(const vector<int> & levels)
{
    for (int i = 0; i < levels.size()-1; i++)
    {
        int difference = levels[i+1] - levels[i];
        if (difference > 3 || difference < -3)
        {   // Unsafe: Reactor increasing or decreasing too quickly
            return false;
        }
    }

    return true;
}


int Day2Solution::twoStarSolution(std::vector<std::string> puzzleInput) {
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
            vector<int> dampenedLevels = levels;
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

bool Day2Solution::levelsAreSafe(vector<int> levels)
{
    // Unsafe: Reactor is not maintaining trend
    if (!trendIsSafe(levels))
        return false;

    // Unsafe: Reactor increasing or decreasing too quickly
    if (!changeIsSafe(levels))
        return false;

    return true;
}