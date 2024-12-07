cmake_minimum_required(VERSION 3.29)
project(AdventOfCode_2024)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdventOfCode_2024 AdventOfCodeMain.cpp
        AdventSolver/AdventSolver.h
        AdventSolver/AllSolutions.h
        AdventSolver/solutions/Solution.h
        AdventSolver/solutions/Day1Solution.cpp
        AdventSolver/solutions/Day1Solution.h
        AdventSolver/solutions/Day2Solution.cpp
        AdventSolver/solutions/Day2Solution.h
        AdventSolver/solutions/Day3Solution.cpp
        AdventSolver/solutions/Day3Solution.h
        AdventSolver/solutions/Day4Solution.cpp
        AdventSolver/solutions/Day4Solution.h
        AdventSolver/solutions/Day5Solution.cpp
        AdventSolver/solutions/Day5Solution.h
        AdventSolver/solutions/Day6Solution.cpp
        AdventSolver/solutions/Day6Solution.h
        AdventSolver/solutions/Day7Solution.cpp
        AdventSolver/solutions/Day7Solution.h
)
