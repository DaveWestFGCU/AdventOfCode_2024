/** Dev: Dave West
 * Date: December 19, 2024
 * Desc: Method definitions for the AoC 2024 day 19 puzzle.
 */

#include "Day19Solution.h"

#include <sstream>
#include <algorithm>


Day19Solution::Day19Solution(const vector<string> &puzzleInput)
    : title("--- Day 19: Linen Layout ---")
{
    for (int line = 0; line < puzzleInput.size(); ++line)
    {
        if (line == 0)
        {
            std::stringstream ss(puzzleInput[line]);
            string towel;
            while (std::getline(ss, towel, ','))
            {
                // Remove preceeding spaces
                if (towel[0] == ' ')
                    towel = towel.substr(1,towel.length()-1);
                towelPatterns.push_back(towel);
            }

            continue;
        }

        if (!puzzleInput[line].empty())
            designs.push_back(puzzleInput[line]);
    }
    sortPatterns();
}


void Day19Solution::printTowels()
{
    for (const auto &towel : towelPatterns)
        std::cout << towel << ",";

    std::cout << std::endl << std::endl;

    for (const auto &towelDesign : designs)
        std::cout << towelDesign << std::endl;

}


void Day19Solution::sortPatterns()
{
    std::ranges::sort(towelPatterns, []
        (const std::string &first, const std::string &second)
        {
            return first.length() > second.length();
        }
    );
}


string Day19Solution::oneStarSolution()
{
    int possibleDesigns {0};

    for (const auto &design : designs)
        if (isPossible(design))
            ++possibleDesigns;

    return std::to_string(possibleDesigns);
}


bool Day19Solution::isPossible(const string& design)
{
    return findNextTowel(design).empty();
}


string Day19Solution::findNextTowel(string design)
{
    for (const auto &pattern : towelPatterns)
    {
        if (pattern.length() > design.length())
            continue;

        if (design.substr(design.length()-pattern.length(),pattern.length()) == pattern)
        {
            string newDesign = findNextTowel(design.substr(0, design.length()-pattern.length()));

            if (newDesign.empty())
                return newDesign;
        }
    }

    return design;
}


string Day19Solution::twoStarSolution()
{
    long long totalDesignPossibilities {0};

    for (const auto &design : designs)
        totalDesignPossibilities += countPossibilities(design);

    return std::to_string(totalDesignPossibilities);
}


long long Day19Solution::countPossibilities(const string &design)
{
    // Base case: All design colors have been found in patterns
    if (design.empty())
        return 1;

    // Base case: Remaining design has been seen before
    if (possibilityCounts.contains(design))
        return possibilityCounts[design];

    // Recursive case: Design has colors unaccounted for.
    possibilityCounts[design] = 0;

    for (const auto &pattern : towelPatterns)
    {
        // Skip pattern if it's longer than the remaining design.
        if (pattern.length() > design.length())
            continue;

        // Check if the last colors of the design matches the pattern
        if (design.substr(design.length()-pattern.length(),pattern.length()) == pattern)
            possibilityCounts[design] += countPossibilities(design.substr(0, design.length()-pattern.length()));
    }

    return possibilityCounts[design];
}

