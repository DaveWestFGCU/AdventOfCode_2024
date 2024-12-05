/*  Dev: Dave West
 * Date: December 5, 2024
 * Desc: Method definitions for the AoC 2024 day 5 puzzle.
 */

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
        {
            auto[beforePage, afterPage] = parsePageOrderingRule(puzzleLine);
            beforeList[afterPage].push_back(beforePage);
            afterList[beforePage].push_back(afterPage);
        }
        else
            updates.push_back(parseUpdate(puzzleLine));

    }   //  end puzzleInput loop

        // Sort Lists
    for (auto & beforePage : beforeList)
        if (!beforePage.empty())
            std::sort(beforePage.begin(), beforePage.end());

    for (auto & afterPage : afterList)
        if (!afterPage.empty())
            std::sort(afterPage.begin(), afterPage.end());
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
    for (const auto & update : updates)
    {
        if (isUpdateInOrder(update))
        {
            size_t midpoint = (update.size() - 1) / 2;
            answer += update[midpoint];
        }
    }

    return static_cast<int>(answer);
}


bool Day5Solution::isUpdateInOrder(vector<int> update)
{
    for (int pageIndex = 0; pageIndex < update.size(); pageIndex++)
    {
            // Compare pages left of current page to list of pages that must be right.
        for (int lookBehind = 0; lookBehind < pageIndex; lookBehind++)
        {
            for (const auto & afterPage : afterList[update[pageIndex]])
            {
                if (update[lookBehind] == afterPage)
                    return false;
            }
        }

            // Compare pages right of current page to list of pages that must be left.
        for (int lookAhead = pageIndex+1; lookAhead < update.size(); lookAhead++)
        {
            for (const auto & beforePage : beforeList[update[pageIndex]])
            {
                if (update[lookAhead] == beforePage)
                    return false;
            }
        }
    }

    return true;
}


int Day5Solution::twoStarSolution()
{
    size_t answer {0};

    for (const auto & update : updates)
    {
        if (!isUpdateInOrder(update))
        {
            vector<int> reorderedUpdate = reorderUpdate(update);

            size_t midpoint = (reorderedUpdate.size() - 1) / 2;
            answer += reorderedUpdate[midpoint];
        }
    }

    return static_cast<int>(answer);
}


vector<int> Day5Solution::reorderUpdate(const vector<int> & update)
{
    vector<int> reorderedUpdate;

    for (const auto & newPage : update)
    {
        size_t newPageIndex = 0;

            // Compare each page in the new, ordered update with previous pages, insert when a page is found that is not
            // in the list of pages that come before the current page.
        for (const auto & orderedPage : reorderedUpdate)
        {
            for (const auto & beforePage : beforeList[newPage])
            {
                if (orderedPage == beforePage)
                    newPageIndex++;
            }
        }
        reorderedUpdate.insert(reorderedUpdate.begin()+newPageIndex, newPage);
    }

    return reorderedUpdate;
}

