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
        AdventSolver/solutions/Day8Solution.cpp
        AdventSolver/solutions/Day8Solution.h
        AdventSolver/solutions/Day9Solution.cpp
        AdventSolver/solutions/Day9Solution.h
        AdventSolver/solutions/Day10Solution.cpp
        AdventSolver/solutions/Day10Solution.h
        AdventSolver/solutions/Day11Solution.cpp
        AdventSolver/solutions/Day11Solution.h
        AdventSolver/solutions/data_structures/LinkedList.cpp
        AdventSolver/solutions/data_structures/LinkedList.h
        AdventSolver/solutions/Day12Solution.cpp
        AdventSolver/solutions/Day12Solution.h
        AdventSolver/solutions/data_structures/Grid.cpp
        AdventSolver/solutions/data_structures/Grid.h
        AdventSolver/solutions/Day13Solution.cpp
        AdventSolver/solutions/Day13Solution.h
        AdventSolver/solutions/Day14Solution.cpp
        AdventSolver/solutions/Day14Solution.h
        AdventSolver/solutions/Day15Solution.cpp
        AdventSolver/solutions/Day15Solution.h
        AdventSolver/solutions/Day16Solution.cpp
        AdventSolver/solutions/Day16Solution.h
        AdventSolver/solutions/data_structures/Graph.cpp
        AdventSolver/solutions/data_structures/Graph.h
        AdventSolver/solutions/data_structures/Graph.cpp
        AdventSolver/solutions/data_structures/Graph.h
        AdventSolver/solutions/Day17Solution.cpp
        AdventSolver/solutions/Day17Solution.h
        AdventSolver/solutions/Day18Solution.cpp
        AdventSolver/solutions/Day18Solution.h
)
