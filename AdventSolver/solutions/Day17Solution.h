/** Dev: Dave West
 * Date: December 17, 2024
 * Desc: Class declarations for the AoC 2024 day 17 puzzle solution and solution factory.
**/

#ifndef DAY17SOLUTION_H
#define DAY17SOLUTION_H

#include "Solution.h"
#include "../AdventSolver.h"
#include <utility>
#include <vector>
#include <string>
#include <cmath>

using std::vector, std::string;

class Day17Solution : public Solution {
    string title;
    class Computer
    {
        long registerA, registerB, registerC;
        vector<int> program;
        int instructionPointer;
        string output;

        [[nodiscard]] long combo(const long &operand) const;
        void runOpcode(const int &opCode, const long &operand);
        void adv(long comboOperand); //  opcode 0
        void bxl(long operand);      //  opcode 1
        void bst(long comboOperand); //  opcode 2
        void jnz(long operand);      //  opcode 3
        void bxc();                  //  opcode 4
        void out(long comboOperand); //  opcode 5
        void bdv(long comboOperand); //  opcode 6
        void cdv(long comboOperand); //  opcode 7

    public:
        Computer() : registerA(0), registerB(0), registerC(0), instructionPointer(0) {}
        Computer(const int &regA, const int &regB, const int &regC, vector<int> prog)
            : registerA(regA), registerB(regB), registerC(regC), program(std::move(prog)), instructionPointer(0) {}

        void runInstructions();
        string getOutput() { return output; }
    };
    Computer device;

    void parseDebugger(const vector<string> &puzzleInput);

public:
    explicit Day17Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    long long oneStarSolution() override;
    long long twoStarSolution() override;
};


class Day17Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day17Solution>(puzzleInput);
    }
};



#endif //DAY17SOLUTION_H
