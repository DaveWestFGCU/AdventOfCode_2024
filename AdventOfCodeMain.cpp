/** Dev: Dave West
 * Date: December 4, 2024
 * Desc: Main program hub for my AoC 2024 solutions.
 *  Log: 12/ 4/24 - Added days 1-4 into current project.
 *       12/ 5/24 - Added day 5 solution.
 *       12/ 6/24 - Added day 6 solution.
 *       12/ 7/24 - Added day 7 solution.
 *                  Added simultaneous display of real/example answers for debugging.
 *       12/ 8/24 - Added day 8 solution.
 *       12/ 9/24 - Added day 9 solution.
 *       12/10/24 - Added day 10 solution.
 *       12/11/24 - Added day 11 solution.
 *       12/12/24 - Added day 12 solution.
 *       12/13/24 - Added day 13 solution.
 *       12/14/24 - Added day 14 solution.
 *       12/15/24 - Added day 15 solution.
 *       12/16/24 - Added day 16 solution.
 *       12/17/24 - Added day 17 solution.
 *       12/18/24 - Added day 18 solution.
 *       12/19/24 - Added day 19 solution.
 *       12/20/24 - Added day 20 solution.
 *       12/21/24 - Added day 21 solution.
 */

#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"


// -------------------------------------------|    DEBUGGING SETTINGS    |------------------------------------------- //

constexpr bool DEBUG = false; // Set to true for solving a single puzzle
enum SolutionType { EXAMPLE, PUZZLE, BOTH_TYPES };
constexpr SolutionType TYPE = BOTH_TYPES;

enum SolutionDifficulty { ONE_STAR, TWO_STAR, BOTH_STARS };
constexpr SolutionDifficulty DIFFICULTY = BOTH_STARS;

constexpr bool VERBOSE_INPUT = false;
constexpr unsigned short TODAY = 21;


// -----------------------------------------|    FUNCTION DECLARATIONS     |----------------------------------------- //

std::unique_ptr<AdventSolver> getDaySolver(const unsigned short &dayNumber);


// --------------------------------------------------|    MAIN    |-------------------------------------------------- //

int main()
{
    for (unsigned short dayNumber = DEBUG? TODAY : 1; dayNumber <= TODAY; ++dayNumber)
    {
        // Day 16 is broken, skip for now.
        if (dayNumber == 16)
            continue;

        std::string inputFilepath = "../puzzle_inputs/";
        std::string inputFilename = "day" + std::to_string(dayNumber) + ".txt";
        std::unique_ptr<AdventSolver> aocSolver = getDaySolver(dayNumber);

        if (aocSolver == nullptr)   // Guard clause for Day##Solution class not found.
            return 1;

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

            std::cout << std::endl << exampleSolution->getTitle() << std::endl;

            switch(TYPE)
            {
                case EXAMPLE:
                case BOTH_TYPES:
                    switch(DIFFICULTY)
                    {
                        case ONE_STAR:
                        case BOTH_STARS:
                            std::cout << "  * Example Answer: " << exampleSolution->oneStarSolution() << std::endl;
                        if constexpr (DIFFICULTY == ONE_STAR)
                            break;

                        case TWO_STAR:
                            std::cout << " ** Example Answer: " << exampleSolution->twoStarSolution() << std::endl;
                        break;
                    }
                    if constexpr (TYPE == EXAMPLE)
                        break;
                    else
                        std::cout << std::endl;

                case PUZZLE:
                    // Solution on real puzzle
                    inputFilepath += inputFilename;
                    puzzleInput = AdventSolver::getInput(inputFilepath, VERBOSE_INPUT?VERBOSE:SILENT);
                    auto solution = aocSolver->create_solution(puzzleInput);

                    switch(DIFFICULTY)
                    {
                        case ONE_STAR:
                        case BOTH_STARS:
                            std::cout << "  * Answer: " << solution->oneStarSolution() << std::endl;
                        if constexpr (DIFFICULTY == ONE_STAR)
                            break;

                        case TWO_STAR:
                            std::cout << " ** Answer: " << solution->twoStarSolution() << std::endl;
                    }
                    break;
            }
        }
    }

    return 0;
}


// ---------------------------------------------| FUNCTION DEFINITIONS |--------------------------------------------- //

std::unique_ptr<AdventSolver> getDaySolver(const unsigned short &dayNumber)
{
    switch(dayNumber)
    {
        case 1:
            return std::make_unique<Day1Creator>();

        case 2:
            return std::make_unique<Day2Creator>();

        case 3:
            return std::make_unique<Day3Creator>();

        case 4:
            return std::make_unique<Day4Creator>();

        case 5:
            return std::make_unique<Day5Creator>();

        case 6:
            return std::make_unique<Day6Creator>();

        case 7:
            return std::make_unique<Day7Creator>();

        case 8:
            return std::make_unique<Day8Creator>();

        case 9:
            return std::make_unique<Day9Creator>();

        case 10:
            return std::make_unique<Day10Creator>();

        case 11:
            return std::make_unique<Day11Creator>();

        case 12:
            return std::make_unique<Day12Creator>();

        case 13:
            return std::make_unique<Day13Creator>();

        case 14:
            return std::make_unique<Day14Creator>();

        case 15:
            return std::make_unique<Day15Creator>();

        case 16:
            return std::make_unique<Day16Creator>();

        case 17:
            return std::make_unique<Day17Creator>();

        case 18:
            return std::make_unique<Day18Creator>();

        case 19:
            return std::make_unique<Day19Creator>();

        case 20:
            return std::make_unique<Day20Creator>();

        case 21:
            return std::make_unique<Day21Creator>();

        default:
            std::cout << "No solution available for day " << dayNumber << "." << std::endl;
            return nullptr;
    }
}


