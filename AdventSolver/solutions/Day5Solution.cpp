

#include "Day5Solution.h"


Day5Solution::Day5Solution(const std::vector<std::string> & puzzleInput)
{
    title = "--- Day 5: Print Queue ---";
    parsePuzzleInput(puzzleInput);
}


void Day5Solution::parsePuzzleInput(const std::vector<std::string> & puzzleInput)
{
    bool pageRules = true;
    for (const auto & puzzleLine : puzzleInput)
    {
            // There is an empty line in the input separating page ordering rules from updates
        if (puzzleLine.empty())
        {
            pageRules = false;
            continue;
        }

        if (pageRules)
            pageOrderingRules.push_back(parsePageOrderingRule(puzzleLine));
        else
            updates.push_back(parseUpdate(puzzleLine));

    }   //  end puzzleInput loop
}   //  end parsePuzzleInput


Day5Solution::PageRule Day5Solution::parsePageOrderingRule(const std::string & unparsedPageRule)
{
    int pipeIndex;
    for (pipeIndex = 0; pipeIndex < unparsedPageRule.length(); pipeIndex++)
        if (unparsedPageRule[pipeIndex] == '|')
            break;


    size_t firstNum = std::stoi(unparsedPageRule.substr(0,pipeIndex));
    size_t lastNumDigits = unparsedPageRule.length()-(pipeIndex+1);
    size_t lastNum  = std::stoi(unparsedPageRule.substr(pipeIndex+1, lastNumDigits));
    return PageRule{firstNum,lastNum};
}


vector<int> Day5Solution::parseUpdate(const std::string & unparsedUpdate)
{
    vector<int> update;
    int value {0};

    for (int i = 0; i < unparsedUpdate.length(); i++)
    {
        if (isDigit(unparsedUpdate[i]))
            value = value * 10 + (unparsedUpdate[i] - '0');

        else if (unparsedUpdate[i] == ',')
        {
            update.push_back(value);
            value = 0;
        }
    }
        // List of values ends with no comma
    update.push_back(value);

    return update;
}


bool Day5Solution::isDigit(const char & character)
{
    if (0 <= character - '0' && character - '0' <= 9)
        return true;

    return false;
}


int Day5Solution::oneStarSolution()
{
    size_t answer {0};

    return static_cast<int>(answer);
}

int Day5Solution::twoStarSolution()
{
    size_t answer {0};

    return static_cast<int>(answer);
}

