/*  Dev: Dave West
 * Date: December 5, 2024
 * Desc: Method definitions for the AoC 2024 day 5 puzzle.
 */

#include "Day5Solution.h"

/**
 * Constructor for the day 5 solution.
 * @param puzzleInput Day 5 puzzle input from AdventOfCode.com.
 */
Day5Solution::Day5Solution(const std::vector<std::string> & puzzleInput)
{
    title = "--- Day 5: Print Queue ---";
    parsePuzzleInput(puzzleInput);
}


/**
 * Parses the puzzle text and loads beforeList, afterList, and updates member variables.
 * @param puzzleInput Day 5 puzzle input from AdventOfCode.com.
 */
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


/**
 * Breaks down a page rule into two numbers and returns them in an ordered pair.
 * @param unparsedPageRule A page rule in the form of "num1|num2"
 * @return Returns the numbers parsed in an ordered pair {firstNum, lastNum}.
 */
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


/**
 * Parses an update into its pages.
 * @param unparsedUpdate A string with a series of page numbers delimited by a comma with no whitespace.
 * @return Returns the pages (integers) from the update.
 */
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


/**
 * Checks if a character is a digit (0-9).
 * @param character Character to check.
 * @return True if character is '0' to '9'.
 */
bool Day5Solution::isDigit(const char & character)
{
    if (0 <= character - '0' && character - '0' <= 9)
        return true;

    return false;
}


/**
 * Solution to the one-star problem.
 * @return The sum of the middle page number from ordered updates.
 */
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


/**
 * Checks if the update obeys the page ordering rules.
 * @param update An update (consisting of page numbers) to check.
 * @return True if the update obeys page ordering rules.
 */
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


/**
 * Solution to the two-star problem.
 * @return The sum of the middle page number of unordered updates, after being ordered.
 */
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


/**
 * Takes an unordered update and orders it according to the page ordering rules.
 * @param update An unordered update.
 * @return An ordered update.
 */
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

