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
    std::sort(towelPatterns.begin(), towelPatterns.end(), []
        (const std::string& first, const std::string& second){
            return first.size() > second.size();
        });
}


string Day19Solution::oneStarSolution()
{
    int possibleDesigns {0};

    for (const auto &design : designs)
    {
        std::cout << design << " : ";
        if (isPossible(design))
        {
            std::cout << "true" << std::endl;
            ++possibleDesigns;
        }
        else
            std::cout << "false" << std::endl;
    }

    return std::to_string(possibleDesigns);
}


bool Day19Solution::isPossible(const string design)
{
    std::cout << std::endl;
    return findNextTowel(design).empty();
}


string Day19Solution::findNextTowel(string design)
{
    for (const auto &pattern : towelPatterns)
    {
        // std::cout << design.substr(design.length()-pattern.length(),pattern.length()) << " == " << pattern << " ? " << std::endl;
        if (pattern.length() > design.length())
            continue;

        if (design.substr(design.length()-pattern.length(),pattern.length()) == pattern)
        {
            std::cout << design << " - " << pattern << " = " << design.substr(0, design.length()-pattern.length()) << std::endl;
            string newDesign = findNextTowel(design.substr(0, design.length()-pattern.length()));

            if (newDesign.empty())
                return newDesign;
        }
    }

    return design;
}



string Day19Solution::twoStarSolution()
{
    int result {0};

    return std::to_string(result);
}
