/*  Dev: Dave West
 * Date: December 4, 2024
 * Desc: Main program hub for my AoC 2024 solutions.
 *  Log: 12/ 4/24 - Added days 1-4 into current project.
 *       12/ 5/24 - Added day 5 solution.
 *       12/ 6/24 - Added day 6 solution.
 *       12/ 7/24 - Added day 7 solution. Added simultaneous display of real/example answers for debugging.
 *       12/ 8/24 - Added day 8 solution.
 *       12/ 9/24 - Added day 9 solution.
 *       12/10/24 - Added day 10 solution.
 *       12/11/24 - Added day 11 solution.
 */

#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"

constexpr bool DEBUG = false; // Set to true for solving a single puzzle
enum DisplaySolutions {ONE_STAR, TWO_STAR, BOTH};
constexpr DisplaySolutions SOLUTIONS = ONE_STAR;
constexpr bool VERBOSE_INPUT = false;
constexpr short TODAY = 11;

int main()
{
    for (size_t day = (DEBUG ? TODAY : 1); day <= TODAY; day++)
    {
        std::string inputFilepath = "../puzzle_inputs/";
        std::string inputFilename = "day" + std::to_string(day) + ".txt";
        std::unique_ptr<AdventSolver> aocSolver;
        switch(day)
        {
            case 1:
                aocSolver = std::make_unique<Day1Creator>();
                break;

            case 2:
                aocSolver = std::make_unique<Day2Creator>();
                break;

            case 3:
                aocSolver = std::make_unique<Day3Creator>();
                break;

            case 4:
                aocSolver = std::make_unique<Day4Creator>();
                break;

            case 5:
                aocSolver = std::make_unique<Day5Creator>();
                break;

            case 6:
                aocSolver = std::make_unique<Day6Creator>();
                break;

            case 7:
                aocSolver = std::make_unique<Day7Creator>();
                break;

            case 8:
                aocSolver = std::make_unique<Day8Creator>();
                break;

            case 9:
                aocSolver = std::make_unique<Day9Creator>();
                break;

            case 10:
                aocSolver = std::make_unique<Day10Creator>();
                break;

            case 11:
                aocSolver = std::make_unique<Day11Creator>();
                break;

            default:
                std::cout << "No solution available for day " << day << "." << std::endl;
        }

        if constexpr (!DEBUG)
        {       // Only shows answers to puzzle input.
            std::vector<std::string> puzzleInput = AdventSolver::getInput(inputFilepath + inputFilename);
            auto solution = aocSolver->create_solution(puzzleInput);

            std::cout << std::endl
                      << solution->getTitle() << std::endl
                      << "  * Answer: " << solution->oneStarSolution() << std::endl
                      << " ** Answer: " << solution->twoStarSolution() << std::endl;
        }
        else
        {       // Debugging Output (shows example answers as well)
                // Solution on example puzzle
            string exampleFilepath =  inputFilepath + "example/" + inputFilename;
            std::vector<std::string> puzzleInput = AdventSolver::getInput(exampleFilepath, VERBOSE_INPUT?VERBOSE:SILENT);
            auto exampleSolution = aocSolver->create_solution(puzzleInput);

            std::cout << std::endl
                      << exampleSolution->getTitle() << std::endl
                      << "  * Example Answer: " << exampleSolution->oneStarSolution() << std::endl
                      << " ** Example Answer: " << exampleSolution->twoStarSolution() << std::endl;

                // Solution on real puzzle
            inputFilepath += inputFilename;
            puzzleInput = AdventSolver::getInput(inputFilepath, VERBOSE_INPUT?VERBOSE:SILENT);
            auto solution = aocSolver->create_solution(puzzleInput);

            std::cout << std::endl
                      << "  * Answer: " << solution->oneStarSolution() << std::endl
                      << " ** Answer: " << solution->twoStarSolution() << std::endl;
        }
    }

    return 0;
}