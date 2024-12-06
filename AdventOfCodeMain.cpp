/*  Dev: Dave West
 * Date: December 4, 2024
 * Desc: Main program hub for my AoC 2024 solutions.
 *  Log: 12/4/24 - Added days 1-4 into current project.
 *  Log: 12/5/24 - Added day 5 solution.
 */

#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"

int main() {
    size_t today = 6;
    bool seeAll = false;     // Set to false for solving current puzzle

    for (size_t day = seeAll ? 1 : today; day <= today; day++)
    {
        std::string inputFilepath = "../puzzle_inputs/";
        std::unique_ptr<AdventSolver> aocSolver;
        switch(day)
        {
            case 1:
                inputFilepath += "day1.txt";
                aocSolver = std::make_unique<Day1Creator>();
                break;

            case 2:
                inputFilepath += "day2.txt";
                aocSolver = std::make_unique<Day2Creator>();
                break;

            case 3:
                inputFilepath += "day3.txt";
                aocSolver = std::make_unique<Day3Creator>();
                break;

            case 4:
                inputFilepath += "day4.txt";
                aocSolver = std::make_unique<Day4Creator>();
                break;

            case 5:
                inputFilepath += "day5.txt";
                aocSolver = std::make_unique<Day5Creator>();
                break;

            case 6:
                inputFilepath += "day6.txt";
                aocSolver = std::make_unique<Day6Creator>();
                break;

            default:
                std::cout << "No solution available for day " << day << "." << std::endl;
        }

        std::vector<std::string> puzzleInput = AdventSolver::getInput(inputFilepath);
        auto solution = aocSolver->create_solution(puzzleInput);

        std::cout << std::endl
                  << solution->getTitle() << std::endl
                  << "  * Answer: " << solution->oneStarSolution() << std::endl
                  << " ** Answer: " << solution->twoStarSolution() << std::endl;
    }

    return 0;
}