/*  Dev: Dave West
 * Date: December 7, 2024
 * Desc: Method definitions for the AoC 2024 day 7 puzzle.
 */

#include "Day7Solution.h"


Day7Solution::Day7Solution(const vector<string>& puzzleInput)
{
    title = "--- Day 7: Bridge Repair ---";
    addCalibrations(puzzleInput);
}


void Day7Solution::addCalibrations(const vector<string>& puzzleInput)
{
    for (auto line : puzzleInput)
    {
        size_t calibrationResult;
        std::vector<size_t> calibrationNumbers;
        std::stringstream ss;

        ss << line;

        bool result {true};
        size_t number;
        while (ss >> number)
        {
            if (result)
            {
                calibrationResult = number;
                result = false;
                ss.ignore(128,':');     // Ignore the colon after the result
            }
            else
                calibrationNumbers.push_back(number);
        }
        calibrations[calibrationResult] = calibrationNumbers;
    }
}


int Day7Solution::oneStarSolution()
{
    size_t totalCalibrationResult {0};

    for (const auto& [result, numbers] : calibrations)
        if (equationSolutionExists(result, numbers))
            totalCalibrationResult += result;
    std::cout << totalCalibrationResult << std::endl;
    return totalCalibrationResult;
}


bool Day7Solution::equationSolutionExists(const size_t& result, const vector<size_t>& numbers)
{
    bool bottomReached {false};
    if (add(result, numbers, 0, 0, bottomReached) == result && bottomReached)
        return true;
    if (multiply(result, numbers, 0, 0, bottomReached) == result && bottomReached)
        return true;

    return false;
}


size_t Day7Solution::add(const size_t& result, const vector<size_t>& numbers, size_t index, size_t currentResult, bool& bottomReached)
{
        // Early return if we pass the result.
    if (currentResult > result)
        return currentResult;

    if (index == numbers.size())
        return currentResult;

        // Equations may work without all numbers.
    if (index+1 == numbers.size())
        bottomReached = true;

    currentResult += numbers[index];

    size_t addResult = add(result, numbers, index+1, currentResult, bottomReached);
    if (addResult == result)
        return addResult;           // Early return, we only need to find that one equation works.

    size_t multiplyResult = multiply(result, numbers, index+1, currentResult, bottomReached);
    if (multiplyResult == result)
        return multiplyResult;      // Early return, we only need to find that one equation works.

    return currentResult;
}


size_t Day7Solution::multiply(const size_t& result, const vector<size_t>& numbers, size_t index, size_t currentResult, bool& bottomReached)
{
    // Early return if we pass the result.
    if (currentResult > result)
        return currentResult;

    if (index == numbers.size())
        return currentResult;

    // Equations may work without all numbers.
    if (index+1 == numbers.size())
        bottomReached = true;

    currentResult *= numbers[index];

    size_t addResult = add(result, numbers, index+1, currentResult, bottomReached);
    if (addResult == result)
        return addResult;           // Early return, we only need to find that one equation works.

    size_t multiplyResult = multiply(result, numbers, index+1, currentResult, bottomReached);
    if (multiplyResult == result)
        return multiplyResult;      // Early return, we only need to find that one equation works.

    return currentResult;
}


int Day7Solution::twoStarSolution()
{
    int result {0};

    return result;
}
