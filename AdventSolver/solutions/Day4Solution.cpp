/*  Dev: Dave West
 * Date: December 4, 2024
 * Desc: Method definitions for the AoC 2024 day 4 puzzle.
 *  Log: 12/ 4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/ 7/2024 - Refactored integer to long long or size_t.
 *                   Refactored puzzle parsing from regex to stringstream.
 *       12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#include "Day4Solution.h"


Day4Solution::Day4Solution(const std::vector<std::string> & puzzleInput)
{
    title = "--- Day 4: Ceres Search ---";
    this->puzzleInput = puzzleInput;
}


string Day4Solution::oneStarSolution()
{
    size_t xmasCount {0};
    const std::regex xmasPattern(R"(XMAS)");
    const std::regex samxPattern(R"(SAMX)");

    xmasCount += countHorizontal(xmasPattern);
    xmasCount += countHorizontal(samxPattern);

    xmasCount += countVertical(xmasPattern);
    xmasCount += countVertical(samxPattern);

    xmasCount += countForwardDiagonal(xmasPattern);
    xmasCount += countForwardDiagonal(samxPattern);

    xmasCount += countBackwardDiagonal(xmasPattern);
    xmasCount += countBackwardDiagonal(samxPattern);

    return std::to_string(xmasCount);
}


size_t Day4Solution::countHorizontal(const std::regex & pattern)
{
    size_t horizontalCount {0};

    for (auto line : puzzleInput)
    {
        std::sregex_iterator match(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        while (match != end)
        {
            horizontalCount++;
            ++match;
        }
    }

    return horizontalCount;
}


size_t Day4Solution::countVertical(const std::regex & pattern)
{
    size_t verticalCount {0};

    for (size_t col = 0; col < puzzleInput[0].length(); col++)
    {
        string columnText;

            // Add all chars in column "col" to a string
        for (const auto & rowText : puzzleInput)
            columnText += rowText[col];

            // Search column text string for forwards or backwards matches.
        std::sregex_iterator match(columnText.begin(), columnText.end(), pattern);
        std::sregex_iterator end;

        while (match != end)
        {
            verticalCount++;
            ++match;
        }

    }   // End columns loop

    return verticalCount;
}


size_t Day4Solution::countForwardDiagonal(const std::regex & pattern)
{
    size_t forwardDiagonalCount {0};
    const int numColumns {static_cast<int>(puzzleInput[0].length())};

    for (int shift = 0; shift < numColumns; shift++)
    {
        string forwardDiagonalFromTop;
        for (int index = 0; index < numColumns; index++)
        {
            if (shift + index >= numColumns)
                break;

            forwardDiagonalFromTop += puzzleInput[index][index + shift];
        }

        std::sregex_iterator matchFromTop(forwardDiagonalFromTop.begin(), forwardDiagonalFromTop.end(), pattern);
        std::sregex_iterator end;

        while (matchFromTop != end)
        {
            forwardDiagonalCount++;
            ++matchFromTop;
        }

        string forwardDiagonalFromSide;
        if (shift)
        {
            for (int index = shift; index < puzzleInput.size(); index++)
                forwardDiagonalFromSide += puzzleInput[index][index-shift];
        }

            // Search column text string for forwards or backwards matches.
        std::sregex_iterator matchFromSide(forwardDiagonalFromSide.begin(), forwardDiagonalFromSide.end(), pattern);

        while (matchFromSide != end)
        {
            forwardDiagonalCount++;
            ++matchFromSide;
        }
    }

    return forwardDiagonalCount;
}


size_t Day4Solution::countBackwardDiagonal(const std::regex & pattern)
{
    size_t backwardDiagonalCount {0};
    const int numColumns {static_cast<int>(puzzleInput[0].length())};

    for (int shift = 0; shift < numColumns; shift++)
    {
        string backwardDiagonalFromTop;
        for (int index = 0; index < numColumns; index++)
        {
            if (shift + index >= numColumns)
                break;

            backwardDiagonalFromTop += puzzleInput[index][numColumns - 1 - index - shift];
        }

        std::sregex_iterator matchFromTop(backwardDiagonalFromTop.begin(), backwardDiagonalFromTop.end(), pattern);
        std::sregex_iterator end;

        while (matchFromTop != end)
        {
            backwardDiagonalCount++;
            ++matchFromTop;
        }

        string backwardDiagonalFromSide;
        if (shift)
        {
            for (int index = 0; index < puzzleInput.size(); index++)
            {
                if (shift + index >= numColumns)
                    break;

                backwardDiagonalFromSide += puzzleInput[index + shift][numColumns-(index+1)];
            }
        }

        // Search column text string for forwards or backwards matches.
        std::sregex_iterator matchFromSide(backwardDiagonalFromSide.begin(), backwardDiagonalFromSide.end(), pattern);

        while (matchFromSide != end)
        {
            backwardDiagonalCount++;
            ++matchFromSide;
        }
    }

    return backwardDiagonalCount;
}


string Day4Solution::twoStarSolution()
{
    size_t xmasCount {0};

    for (int row = 1; row < puzzleInput.size()-1; row++)
    {
        for (int col = 1; col < puzzleInput[0].length()-1; col++)
        {
            if (puzzleInput[row][col] == 'A')
            {
                if (isXmas(row, col))
                    xmasCount++;
            }
        }   // End column loop
    }   // End row loop

    return std::to_string(xmasCount);
}


bool Day4Solution::isXmas(const size_t & row, const size_t & col)
{
    string forwardDiagonal  {puzzleInput[row+1][col-1], 'A', puzzleInput[row-1][col+1]};
    string backwardDiagonal {puzzleInput[row-1][col-1], 'A', puzzleInput[row+1][col+1]};

    if (forwardDiagonal == "MAS" or forwardDiagonal == "SAM")
        if (backwardDiagonal == "MAS" or backwardDiagonal == "SAM")
            return true;

    return false;
}