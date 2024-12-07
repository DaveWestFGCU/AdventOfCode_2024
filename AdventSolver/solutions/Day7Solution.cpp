/*  Dev: Dave West
 * Date: December 7, 2024
 * Desc: Method definitions for the AoC 2024 day 7 puzzle.
 *
 *       Originally used an unordered map to store the calibrations with calibration results as keys, but after
 *       hours of pulling my hair out I realized I had a single collision that caused my answer to be off
 *       by that calibration result's amount. Went back to vectors, since I'm just iterating over
 *       calibrations anyway.
 *
 *       Uses recursion to solve whether a calibration can equate to the result.
 */

#include "Day7Solution.h"


Day7Solution::Day7Solution(const vector<string>& puzzleInput)
{
    title = "--- Day 7: Bridge Repair ---";
    addCalibrations(puzzleInput);
}


void Day7Solution::addCalibrations(const vector<string>& puzzleInput)
{
    for (const auto& line : puzzleInput)
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
        calibrations.emplace_back(calibrationResult,calibrationNumbers);
    }
}


long long Day7Solution::oneStarSolution()
{
    size_t totalCalibrationResult {0};

    for (const auto& [result, numbers] : calibrations)
    {
        if (equationSolutionExists(result, numbers, numbers[0], 1))
            totalCalibrationResult += result;
    }

    return static_cast<long long>(totalCalibrationResult);
}


bool Day7Solution::equationSolutionExists(const size_t& result, const vector<size_t>& numbers, size_t currentResult, const size_t index, Feature concatenation)
{
    // Base Case: We ran out of numbers.
    if (index == numbers.size())
    {
        if (currentResult == result)
            return true;

        return false;
    }

    size_t addResult = currentResult + numbers[index];
    if (equationSolutionExists(result, numbers, addResult, index+1, concatenation))
        return true;

    size_t multiplyResult = currentResult * numbers[index];
    if (equationSolutionExists(result, numbers, multiplyResult, index+1, concatenation))
        return true;

    if (concatenation == ON)
    {
        size_t concatenateResult = concatenate(currentResult, numbers[index]);
        if (equationSolutionExists(result, numbers, concatenateResult, index+1, concatenation))
            return true;
    }

    return false;
}


long long Day7Solution::twoStarSolution()
{
    size_t totalCalibrationResult {0};

    for (const auto& [result, numbers] : calibrations)
    {
        if (equationSolutionExists(result, numbers, numbers[0], 1, ON))
            totalCalibrationResult += result;
    }

    return static_cast<long long>(totalCalibrationResult);
}


size_t Day7Solution::concatenate(const size_t& num1, const size_t& num2)
{
    return num1 * static_cast<int>(std::pow(10,getDigits(num2))) + num2;
}


short Day7Solution::getDigits(size_t number)
{
    short numDigits {0};
    while (number)
    {
        number /= 10;
        numDigits++;
    }

    return numDigits;
}