#ifndef ADVENTSOLVER_H
#define ADVENTSOLVER_H

#include <fstream>
#include "solutions/Solution.h"

enum consoleOutput { SILENT, VERBOSE };

class AdventSolver {
public:
    static inline std::vector<std::string> getInput(std::string const& filepath, consoleOutput output = SILENT);

    virtual ~AdventSolver() = default;
    [[nodiscard]] virtual std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const = 0;
};


std::vector<std::string> AdventSolver::getInput(std::string const& filepath, consoleOutput output)
{
    std::ifstream file(filepath);
    std::string str;
    std::vector<std::string> lines;

    if (file.fail())
    {
        std::cerr << "ERROR: No file found at \"" << filepath << "\"!";
        lines.push_back(str);
        return lines;
    }

    if (output == VERBOSE)
        std::cout << "===============|  AdventSolver::getInput  |===============" << std::endl;

    while (std::getline(file, str))
    {
        if (output == VERBOSE)
            std::cout << str << std::endl;
        lines.push_back(str);
    }

    if (output == VERBOSE)
        std::cout << "====================|  End Input  |====================" << std::endl << std::endl;

    return lines;
}

#endif //ADVENTSOLVER_H
