/** Dev: Dave West
 * Date: December 13, 2024
 * Desc: Method definitions for the AoC 2024 day 13 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#include "Day13Solution.h"


Day13Solution::Day13Solution(const vector<string> &puzzleInput)
    : title("--- Day 13: Claw Contraption ---")
{
    parseClawGames(puzzleInput);
}


void Day13Solution::parseClawGames(const vector<string> &puzzleInput)
{
    std::pair<int,int> buttonA, buttonB, prize;

    for (size_t i = 0; i <= puzzleInput.size(); i++)
    {
        switch(i % 4)
        {
            case 0:
                buttonA = parseValues(puzzleInput[i]);
                break;
            case 1:
                buttonB = parseValues(puzzleInput[i]);
                break;
            case 2:
                prize = parseValues(puzzleInput[i]);
                break;
            case 3:
                clawGames.emplace_back(buttonA, buttonB, prize);
                break;
        }
    }
}


std::pair<size_t,size_t> Day13Solution::parseValues(string line)
{
    const std::regex pattern(R"(\d+)");
    std::sregex_iterator match(line.begin(), line.end(), pattern);
    return {std::stoi(match++->str()), std::stoi(match->str())};
}


Day13Solution::ClawGame::ClawGame(const std::pair<size_t,size_t> &buttonA, const std::pair<size_t,size_t> &buttonB, const std::pair<size_t,size_t> &prize)
: buttonA(buttonA.first, buttonA.second), buttonB(buttonB.first, buttonB.second),
  prize(prize.first, prize.second), tokensPerAPress(3), tokensPerBPress(1)
{
    applyCramersRule();
    calculateWinCost();
}


void Day13Solution::ClawGame::applyCramersRule()
{
    // A = (p_x*b_y - prize_y*b_x) / (a_x*b_y - a_y*b_x)
    aPresses = static_cast<double>(prize.x*buttonB.y - prize.y*buttonB.x) / static_cast<double>(buttonA.x*buttonB.y - buttonA.y*buttonB.x);

    // B = (a_x*p_y - a_y*p_x) / (a_x*b_y - a_y*b_x)
    bPresses = static_cast<double>(buttonA.x*prize.y - buttonA.y*prize.x) / static_cast<double>(buttonA.x*buttonB.y - buttonA.y*buttonB.x);
}


void Day13Solution::ClawGame::calculateWinCost()
{
    if (aPresses*buttonA.x + bPresses*buttonB.x == prize.x && aPresses*buttonA.y + bPresses*buttonB.y == prize.y)
        costToWin = tokensPerAPress * aPresses + tokensPerBPress * bPresses;

    else
        costToWin = 0;
}


void Day13Solution::ClawGame::recalibrate(const long long &addend)
{
    prize.x += addend;
    prize.y += addend;

    applyCramersRule();
    calculateWinCost();
}


string Day13Solution::oneStarSolution()
{
    int totalTokens {0};
    for (auto game : clawGames)
        totalTokens += game.winCost();
    return std::to_string(totalTokens);
}


string Day13Solution::twoStarSolution()
{
    size_t totalTokens {0};
    for (auto game : clawGames)
    {
        game.recalibrate(10000000000000);
        totalTokens += game.winCost();
    }
    return std::to_string(totalTokens);
}
