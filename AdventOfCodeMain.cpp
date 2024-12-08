/*  Dev: Dave West
 * Date: December 4, 2024
 * Desc: Main program hub for my AoC 2024 solutions.
 *  Log: 12/4/24 - Added days 1-4 into current project.
 *       12/5/24 - Added day 5 solution.
 *       12/6/24 - Added day 6 solution.
 *       12/7/24 - Added day 7 solution. Added simultaneous display of real/example answers for debugging.
 *       12/8/24 - Added day 8 solution.
 */

#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"

constexpr bool DEBUG = false; // Set to true for solving a single puzzle
constexpr short TODAY = 8;

int main()
{
    for (size_t day = (DEBUG ? TODAY : 1); day <= TODAY; day++)
    {
        std::string inputFilepath = "../puzzle_inputs/";
        std::string inputFilename;
        std::unique_ptr<AdventSolver> aocSolver;
        switch(day)
        {
            case 1:
                inputFilename = "day1.txt";
                aocSolver = std::make_unique<Day1Creator>();
                break;

            case 2:
                inputFilename = "day2.txt";
                aocSolver = std::make_unique<Day2Creator>();
                break;

            case 3:
                inputFilename = "day3.txt";
                aocSolver = std::make_unique<Day3Creator>();
                break;

            case 4:
                inputFilename = "day4.txt";
                aocSolver = std::make_unique<Day4Creator>();
                break;

            case 5:
                inputFilename = "day5.txt";
                aocSolver = std::make_unique<Day5Creator>();
                break;

            case 6:
                inputFilename = "day6.txt";
                aocSolver = std::make_unique<Day6Creator>();
                break;

            case 7:
                inputFilename = "day7.txt";
                aocSolver = std::make_unique<Day7Creator>();
                break;

            case 8:
                inputFilename = "day8.txt";
            aocSolver = std::make_unique<Day8Creator>();
            break;

            default:
                std::cout << "No solution available for day " << day << "." << std::endl;
        }

        if constexpr (!DEBUG)
        {       // Only shows answers to "my" puzzle input.
            std::vector<std::string> puzzleInput = AdventSolver::getInput(inputFilepath + inputFilename);
            auto solution = aocSolver->create_solution(puzzleInput);

            std::cout << std::endl
                      << solution->getTitle() << std::endl
                      << "  * Answer: " << solution->oneStarSolution() << std::endl
                      << " ** Answer: " << solution->twoStarSolution() << std::endl;
        }
        else
        {       // Debugging Output
                // Solution on example puzzle
            std::vector<std::string> puzzleInput = AdventSolver::getInput(inputFilepath + "example/" + inputFilename);
            auto exampleSolution = aocSolver->create_solution(puzzleInput);

            std::cout << std::endl
                      << exampleSolution->getTitle() << std::endl
                      << "  * Example Answer: " << exampleSolution->oneStarSolution() << std::endl
                      << " ** Example Answer: " << exampleSolution->twoStarSolution() << std::endl;

                // Solution on real puzzle
            puzzleInput = AdventSolver::getInput(inputFilepath + inputFilename);
            auto solution = aocSolver->create_solution(puzzleInput);

            std::cout << std::endl
                      << "  * Answer: " << solution->oneStarSolution() << std::endl
                      << " ** Answer: " << solution->twoStarSolution() << std::endl;
        }
    }

    return 0;
}