/** Dev: Dave West
 * Date: December 22, 2024
 * Desc: Method definitions for the AoC 2024 day 22 puzzle.
 */

#include "Day22Solution.h"


Day22Solution::Day22Solution(const vector<string> &puzzleInput)
    : title("--- Day 22: Monkey Market ---")
{
    for (const auto &line : puzzleInput)
        secretNumbers.push_back(std::stoi(line));
}


int Day22Solution::findNextSecretNumber(int secretNumber)
{
    secretNumber = secretNumberEvolutionStep1(secretNumber);
    secretNumber = secretNumberEvolutionStep2(secretNumber);
    return secretNumberEvolutionStep3(secretNumber);
}


int Day22Solution::secretNumberEvolutionStep1(const int &secretNumber)
{
    int value = secretNumber * 64;
    value = value ^ secretNumber;   //  mix
    return value % 16777216;        //  prune
}


int Day22Solution::secretNumberEvolutionStep2(const int &secretNumber)
{
    int value = secretNumber / 32;
    value = value ^ secretNumber;   //  mix
    return value % 16777216;        //  prune
}


int Day22Solution::secretNumberEvolutionStep3(const int &secretNumber)
{
    long long value = static_cast<long long>(secretNumber) * 2048;
    value = value ^ secretNumber;               //  mix
    return static_cast<int>(value % 16777216);  //  prune
}


string Day22Solution::oneStarSolution()
{
    long long secretNumberSum {0};
    for (auto secretNumber : secretNumbers)
    {
        for (int i = 0; i < 2000; ++i)
            secretNumber = findNextSecretNumber(secretNumber);

        secretNumberSum += secretNumber;
    }

    return std::to_string(secretNumberSum);
}


string Day22Solution::twoStarSolution()
{
    findSellSequenceBananaCounts();

    int maxBananas { 0 };
    for (const auto &sellSequence : sellSequences)
    {
        if (sellSequence.second.totalBananas > maxBananas)
            maxBananas = sellSequence.second.totalBananas;
    }

    return std::to_string(maxBananas);
}


void Day22Solution::findSellSequenceBananaCounts()
{
    for (auto &secretNumber : secretNumbers)
    {
        short lastPrice { static_cast<short>(secretNumber % 10) };
        SellSequence lastSellSeq;

        // Reset sell sequence seen values with each new initial secret number
        for (auto &sellSequence : sellSequences)
            sellSequence.second.seen = false;

        for (int i = 0; i < 2000; ++i)
        {
            // Update the sell sequence
            secretNumber = findNextSecretNumber(secretNumber);
            auto currentPrice = static_cast<short>(secretNumber % 10);
            SellSequence currentSellSeq(currentPrice-lastPrice, lastSellSeq);

            // Only start tracking after the initial zeros are removed
            if (i > 2)
            {
                // We only want to add the total for the first occurrence of a sell sequence
                if (!sellSequences[currentSellSeq].seen)
                {
                    sellSequences[currentSellSeq].totalBananas += currentPrice;
                    sellSequences[currentSellSeq].seen = true;
                }
            }
            lastPrice = currentPrice;
            lastSellSeq = currentSellSeq;
        }
    }
}
