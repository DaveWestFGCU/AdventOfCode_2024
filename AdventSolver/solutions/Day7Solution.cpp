/** Dev: Dave West
 * Date: December 7, 2024
 * Desc: Method definitions for the AoC 2024 day 7 puzzle.
 *
 *       Originally used an unordered map to store the calibrations with calibration results as keys, but after
 *       hours of pulling my hair out I realized I had a single collision that caused my answer to be off
 *       by that calibration result's amount. Went back to vectors, since I'm just iterating over
 *       calibrations anyway.
 *
 *       Uses recursion to solve whether a calibration can equate to the result.
 *
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
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


string Day7Solution::oneStarSolution()
{
    size_t totalCalibrationResult {0};

    for (const auto& [result, numbers] : calibrations)
    {
        if (reverseEqnSlnExists(result, numbers, result, numbers.size()-1))
            totalCalibrationResult += result;
    }

    return std::to_string(totalCalibrationResult);
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


/**
 * Optimized solution for determining whether equations exist to satisfy the result.
 * Solves backwrds, finding whether the last element can satisfy multiplication or concatenation,
 * stopping the chain if not. Approx 25x faster.
 * @param result Result to unknown equation.
 * @param numbers Numbers in unknown equation.
 * @param currentResult Keeping track of the result as we reduce it. Aiming to reach 0 with the last element.
 * @param index Next index in numbers to remove from current result.
 * @param concatenation ON for two-star solution
 * @return True if the equation has at least one set of operators that satisfies the result.
 */
bool Day7Solution::reverseEqnSlnExists(const size_t& result, const vector<size_t>& numbers, long long currentResult, const size_t index, Feature concatenation)
{
        // Base Case: We ran out of numbers.
    if (index == -1)
    {
        if (currentResult == 0)
            return true;

        return false;
    }

    if (currentResult < 0)
        return false;

    long long subtractResult = currentResult - numbers[index];
    if (reverseEqnSlnExists(result, numbers, subtractResult, index-1, concatenation))
        return true;

    if (currentResult % numbers[index] == 0)
    {
        size_t divideResult = currentResult / numbers[index];
        if (reverseEqnSlnExists(result, numbers, divideResult, index-1, concatenation))
            return true;
    }

    if (concatenation == ON)
    {
        string stringResult = std::to_string(currentResult);
        string stringNumber = std::to_string(numbers[index]);
        int substringStart = stringResult.length() - stringNumber.length();
        if (stringResult.substr(substringStart,stringNumber.length()) == stringNumber)
        {
            size_t deconcatenateResult = static_cast<size_t>(std::stoll(stringResult.substr(0, substringStart)));
            if (reverseEqnSlnExists(result, numbers, deconcatenateResult, index - 1, concatenation))
                return true;
        }
    }

    return false;
}


string Day7Solution::twoStarSolution()
{
    size_t totalCalibrationResult {0};

    for (const auto& [result, numbers] : calibrations)
    {
        if (equationSolutionExists(result, numbers, numbers[0], 1, ON))
            totalCalibrationResult += result;
    }

    return std::to_string(totalCalibrationResult);
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