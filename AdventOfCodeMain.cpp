#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"

int main() {
    size_t today = 1;
    std::vector<std::string> puzzleInput;

    for (size_t day = 1; day <= today; day++)
    {
        std::unique_ptr<AdventSolver> solver;
        switch(day)
        {
            case 1:
                puzzleInput = AdventSolver::getInput("../puzzle_inputs/day1_puzzle_input.txt");
                solver = std::make_unique<Day1Creator>();
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            default:
                std::cout << "No solution available for day " << day << "." << std::endl;
        }
        auto solution = solver->create_solution(puzzleInput);
        std::cout << solution->getTitle() << std::endl;
        std::cout << "  * Answer: " << solution->oneStarSolution(puzzleInput) << std::endl;
        std::cout << " ** Answer: " << solution->twoStarSolution(puzzleInput) << std::endl;
        std::cout << std::endl;
    }


    return 0;
}