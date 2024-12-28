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


class Day17Solution : public Solution {
    string title;
    class Computer
    {
        long long registerA, registerB, registerC;
        vector<int> program;
        int instructionPointer;
        vector<int> output;

        [[nodiscard]] long long combo(const int &operand) const;
        void runOpcode(const int &opCode, const int &operand);
        void adv(const long long &comboOperand); //  opcode 0
        void bxl(const int &operand);      //  opcode 1
        void bst(const long long &comboOperand); //  opcode 2
        void jnz(const int &operand);      //  opcode 3
        void bxc();                       //  opcode 4
        void out(const long long &comboOperand); //  opcode 5
        void bdv(const long long &comboOperand); //  opcode 6
        void cdv(const long long &comboOperand); //  opcode 7

    public:
        Computer() : registerA(0), registerB(0), registerC(0), instructionPointer(0) {}
        Computer(const long long &regA, const long long &regB, const long long &regC, vector<int> prog)
            : registerA(regA), registerB(regB), registerC(regC), program(std::move(prog)), instructionPointer(0) {}

        void runInstructions();
        void runInstructions(long long registerA);
        vector<int> getOutput() { return output; }
        vector<int> getProgram() { return program; }
    };
    Computer device;

    void parseDebugger(const vector<string> &puzzleInput);

    long long findOriginalRegisterA();
    bool findDigit(const long long &n, const int &digit, long long &foundRegisterA);

public:
    explicit Day17Solution(const vector<string> &puzzleInput);
    [[nodiscard]] std::string getTitle() const override { return title; }
    string oneStarSolution() override;
    string twoStarSolution() override;
};


class Day17Creator : public AdventSolver {
public:
    [[nodiscard]] std::unique_ptr<Solution> create_solution(const std::vector<std::string> & puzzleInput) const override {
        return std::make_unique<Day17Solution>(puzzleInput);
    }
};



#endif //DAY17SOLUTION_H
