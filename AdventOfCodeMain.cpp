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
 *       12/22/24 - Added day 22 solution.
 *       12/23/24 - Added day 23 solution.
 *       12/24/24 - Added Christmas Eve solution.
 *       12/25/24 - Added Christmas solution.
 *       12/29/24 - Refactored solver switch case to map.
 *                  Refactored debugging to use preprocessor macros.
 */

#include <memory>
#include "AdventSolver/AdventSolver.h"
#include "AdventSolver/AllSolutions.h"


// -------------------------------------------|    DEBUGGING SETTINGS    |------------------------------------------- //

#define DEBUG false      // True: Display only today's puzzle.
#define ONE_STAR true   // True: Solve the one-star problem.
#define TWO_STAR true   // True: Solve the two-star problem.
#define EXAMPLE true    // True: Solve example problems.
#define PUZZLE true     // True: Solve given input problem.
constexpr bool VERBOSE_INPUT = false;   // True: Display puzzle input when loading.
constexpr unsigned short TODAY = 25;    // If DEBUG, day to display. Else display from day 1 to TODAY.


// -----------------------------------------|    FUNCTION DECLARATIONS     |----------------------------------------- //

std::unique_ptr<AdventSolver> getDaySolver(const unsigned short &dayNumber);
void solvePuzzle(const AdventSolver *solver, const std::string &inputFilepath, const std::string &inputFilename, bool isDebugging = false);
void handleDebugging(const AdventSolver *solver, const std::string &inputFilepath, const std::string &inputFilename);


// --------------------------------------------------|    MAIN    |-------------------------------------------------- //

int main()
{
#if DEBUG
    unsigned short startDayNumber = TODAY;
#else
    unsigned short startDayNumber = 1;
#endif

    for (int dayNumber = startDayNumber; dayNumber <= TODAY; ++dayNumber)
    {
        std::string inputFilepath = "../puzzle_inputs/";
        std::string inputFilename = "day" + std::to_string(dayNumber) + ".txt";

        std::unique_ptr<AdventSolver> aocSolver = getDaySolver(dayNumber);
        if (aocSolver == nullptr)
            return 1;

#if DEBUG
        handleDebugging(aocSolver.get(), inputFilepath, inputFilename);
#else
        solvePuzzle(aocSolver.get(), inputFilepath, inputFilename);
#endif

    }

    return 0;
}


// ---------------------------------------------| FUNCTION DEFINITIONS |--------------------------------------------- //

/**
 * Pairs the day's number with a lambda function to create that day's solver.
 */
std::map<unsigned short, std::function<std::unique_ptr<AdventSolver>()>> solverMap =
{
    {1,  []() { return std::make_unique<Day1Creator>();  }},
    {2,  []() { return std::make_unique<Day2Creator>();  }},
    {3,  []() { return std::make_unique<Day3Creator>();  }},
    {4,  []() { return std::make_unique<Day4Creator>();  }},
    {5,  []() { return std::make_unique<Day5Creator>();  }},
    {6,  []() { return std::make_unique<Day6Creator>();  }},
    {7,  []() { return std::make_unique<Day7Creator>();  }},
    {8,  []() { return std::make_unique<Day8Creator>();  }},
    {9,  []() { return std::make_unique<Day9Creator>();  }},
    {10, []() { return std::make_unique<Day10Creator>(); }},
    {11, []() { return std::make_unique<Day11Creator>(); }},
    {12, []() { return std::make_unique<Day12Creator>(); }},
    {13, []() { return std::make_unique<Day13Creator>(); }},
    {14, []() { return std::make_unique<Day14Creator>(); }},
    {15, []() { return std::make_unique<Day15Creator>(); }},
    {16, []() { return std::make_unique<Day16Creator>(); }},
    {17, []() { return std::make_unique<Day17Creator>(); }},
    {18, []() { return std::make_unique<Day18Creator>(); }},
    {19, []() { return std::make_unique<Day19Creator>(); }},
    {20, []() { return std::make_unique<Day20Creator>(); }},
    {21, []() { return std::make_unique<Day21Creator>(); }},
    {22, []() { return std::make_unique<Day22Creator>(); }},
    {23, []() { return std::make_unique<Day23Creator>(); }},
    {24, []() { return std::make_unique<Day24Creator>(); }},
    {25, []() { return std::make_unique<Day25Creator>(); }}
};


/**
 * Creates a pointer to a given AoC day for solving. Requires the day's puzzle in a /puzzle_inputs/ directory.
 * @param dayNumber The AoC day number to solve.
 * @return A pointer to the day's product object, created by the day's factory.
 */
std::unique_ptr<AdventSolver> getDaySolver(const unsigned short &dayNumber)
{
    auto iterator = solverMap.find(dayNumber);
    if (iterator != solverMap.end()) {
        return iterator->second();  //  Invoke the function that creates the solver
    }

    std::cout << "No solution available for day " << dayNumber << "." << std::endl;
    return nullptr;
}


/**
 * Solves the problem and displays the solution to console.
 * @param solver Creator for the day.
 * @param inputFilepath Relative path to the input file's directory.
 * @param inputFilename Input file name.
 * @param isDebugging True to not display puzzle title (will have already been displayed).
 */
void solvePuzzle(const AdventSolver *solver, const std::string& inputFilepath, const std::string& inputFilename, const bool isDebugging)
{
    std::vector<std::string> puzzleInput = AdventSolver::getInput(inputFilepath + inputFilename);
    std::unique_ptr<Solution> solution = solver->create_solution(puzzleInput);

    if (!isDebugging)
        std::cout << "\n" << solution->getTitle() << std::endl;

#if ONE_STAR
    std::cout << "  * " << "Answer: " << solution->oneStarSolution() << std::endl;
#endif
#if TWO_STAR
    std::cout << " ** " << "Answer: " << solution->twoStarSolution() << std::endl;
#endif
}


/**
 * Solves and displays example prompts.
 * @param solver Day product creator.
 * @param inputFilepath Relative path to the input file's directory.
 * @param inputFilename Input file name.
 */
void handleDebugging(const AdventSolver *solver, const std::string& inputFilepath, const std::string& inputFilename)
{
    std::string exampleFilepath = inputFilepath + "example/" + inputFilename;
    std::vector<std::string> puzzleInput = AdventSolver::getInput(exampleFilepath, static_cast<consoleOutput>(VERBOSE_INPUT));
    auto exampleSolution = solver->create_solution(puzzleInput);

    std::cout << "\n" << exampleSolution->getTitle() << std::endl;

#if EXAMPLE
    #if ONE_STAR
    std::cout << "  * Example Answer: " << exampleSolution->oneStarSolution() << std::endl;
    #endif ONE_STAR

    #if TWO_STAR
    std::cout << " ** Example Answer: " << exampleSolution->twoStarSolution() << std::endl;
    #endif
#endif

#if PUZZLE
    std::cout << "\n";
    solvePuzzle(solver, inputFilepath, inputFilename, true);
#endif
}