#ifndef ADVENTSOLVER_H
#define ADVENTSOLVER_H

#include <fstream>
#include "solutions/Solution.h"

class AdventSolver {
public:
    enum consoleOutput {silent, verbose};
    static inline std::vector<std::string> getInput(std::string const& filepath, consoleOutput output = silent);

    virtual ~AdventSolver() = default;
    virtual std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const = 0;
};


std::vector<std::string> AdventSolver::getInput(std::string const& filepath, consoleOutput output)
{
    std::ifstream file(filepath);
    std::string str;
    std::vector<std::string> lines;

    if (output == verbose)
        std::cout << "===============|  AdventSolver::getInput  |===============" << std::endl;

    while (std::getline(file, str))
    {
        if (output == verbose)
            std::cout << str << std::endl;
        lines.push_back(str);
    }

    if (output == verbose)
        std::cout << "====================|  End Input  |====================" << std::endl << std::endl;

    return lines;
}

#endif //ADVENTSOLVER_H
