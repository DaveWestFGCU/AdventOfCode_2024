#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"

int main() {
    size_t today = 2;
    std::string inputFilepath;
    std::vector<std::string> puzzleInput;

    for (size_t day = 1; day <= today; day++)
    {
        std::unique_ptr<AdventSolver> solver;
        switch(day)
        {
            case 1:
                inputFilepath = "../puzzle_inputs/day1_puzzle_input.txt";
                solver = std::make_unique<Day1Creator>();
                break;

            case 2:
                inputFilepath = "../puzzle_inputs/day2_puzzle_input.txt";
                solver = std::make_unique<Day2Creator>();
                break;

            case 3:
                break;

            case 4:
                break;

            default:
                std::cout << "No solution available for day " << day << "." << std::endl;
        }

        puzzleInput = AdventSolver::getInput(inputFilepath);
        auto solution = solver->create_solution(puzzleInput);

        std::cout << solution->getTitle() << std::endl;
        std::cout << "  * Answer: " << solution->oneStarSolution(puzzleInput) << std::endl;
        std::cout << " ** Answer: " << solution->twoStarSolution(puzzleInput) << std::endl;
        std::cout << std::endl;
    }


    return 0;
}