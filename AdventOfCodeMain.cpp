/*  Dev: Dave West
 * Date: December 4, 2024
 * Desc: Main program hub for my AoC 2024 solutions.
 */

#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"

int main() {
    size_t today = 3;
    std::string inputFilepath;

    for (size_t day = 1; day <= today; day++)
    {
        std::unique_ptr<AdventSolver> aocSolver;
        switch(day)
        {
            case 1:
                inputFilepath = "../puzzle_inputs/day1_puzzle_input.txt";
                aocSolver = std::make_unique<Day1Creator>();
                break;

            case 2:
                inputFilepath = "../puzzle_inputs/day2_puzzle_input.txt";
                aocSolver = std::make_unique<Day2Creator>();
                break;

            case 3:
                inputFilepath = "../puzzle_inputs/day3_puzzle_input.txt";
                aocSolver = std::make_unique<Day3Creator>();
                break;

            case 4:
                break;

            default:
                std::cout << "No solution available for day " << day << "." << std::endl;
        }

        std::vector<std::string> puzzleInput = AdventSolver::getInput(inputFilepath);
        auto solution = aocSolver->create_solution(puzzleInput);

        std::cout << solution->getTitle() << std::endl;
        std::cout << "  * Answer: " << solution->oneStarSolution() << std::endl;
        std::cout << " ** Answer: " << solution->twoStarSolution() << std::endl;
        std::cout << std::endl;
    }


    return 0;
}