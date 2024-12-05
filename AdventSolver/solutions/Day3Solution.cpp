

#include "Day3Solution.h"


Day3Solution::Day3Solution(const std::vector<std::string> & puzzleInput)
{
    title = "--- Day 3: Mull It Over ---";
    this->puzzleInput = puzzleInput;
}


int Day3Solution::oneStarSolution()
{
    int mulResult {0};
    const std::regex mulPattern(R"(mul\(\d+,\d+\))");

    vector<string> matches;
    for (const auto & memory : puzzleInput)
    {
        std::sregex_iterator match(memory.begin(), memory.end(), mulPattern);
        std::sregex_iterator end;

        while (match != end)
        {
            matches.push_back(match->str());
            ++match;
        }
    }

    const std::regex numberPattern(R"(\d+)");
    for (auto match : matches)
    {
        std::sregex_iterator numbers(match.begin(), match.end(), numberPattern);
        mulResult += std::stoi(numbers->str()) * std::stoi((++numbers)->str());
    }

    return mulResult;
}


int Day3Solution::twoStarSolution()
{
    int mulResult {0};

    // Extract commands from memory (string)
    const std::regex mulPattern(R"(do\(\)|don't\(\)|mul\(\d+,\d+\))");
    vector<string> commands;
    for (const auto & memory : puzzleInput)
    {
        std::sregex_iterator match(memory.begin(), memory.end(), mulPattern);
        std::sregex_iterator end;

        while (match != end)
        {
            commands.push_back(match->str());
            ++match;
        }
    }

    // Run commands, line by line
    bool mulEnabled = true;
    const std::regex numberPattern(R"(\d+)");
    for (auto command : commands)
    {
        if (command == "do()")
            mulEnabled = true;

        else if (command == "don't()")
            mulEnabled = false;

        else if (mulEnabled)
        {
            std::sregex_iterator numbers(command.begin(), command.end(), numberPattern);
            mulResult += std::stoi(numbers->str()) * std::stoi((++numbers)->str());
        }
    }

    return mulResult;
}
