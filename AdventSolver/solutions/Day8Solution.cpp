/*  Dev: Dave West
 * Date: December 8, 2024
 * Desc: Method definitions for the AoC 2024 day 8 puzzle.
 */

#include "Day8Solution.h"


Day8Solution::Day8Solution(const vector<string>& puzzleInput)
{
    title = "--- Day 8: Resonant Collinearity ---";
    buildAntennaPositionLists(puzzleInput);
    printFrequencies();
}


void Day8Solution::buildAntennaPositionLists(const vector<string>& puzzleInput)
{
    for (size_t row = 0; row < puzzleInput.size(); row++)
    {
        for (size_t col = 0; col < puzzleInput[0].length(); col++)
        {
            char letter = puzzleInput[row][col];
            if (letter == '.')  // '.' is empty space
                continue;

            frequencyLocations[letter].push_back(Pos{row,col});
        }
    }
}


void Day8Solution::printFrequencies()
{
    for (auto frequency_it = frequencyLocations.begin(); frequency_it != frequencyLocations.end(); ++frequency_it)
    {
        std::cout << "Key: " << frequency_it->first << ", Value: ";
        for (auto position_it = frequency_it->second.begin(); position_it != frequency_it->second.end(); ++position_it)
        {
            std::cout << "(" << position_it->x << ", " << position_it->y << "), ";
        }
        std::cout << std::endl;
    }
}



long long Day8Solution::oneStarSolution()
{
    int result {0};

    return result;
}


long long Day8Solution::twoStarSolution()
{
    int result {0};

    return result;
}
