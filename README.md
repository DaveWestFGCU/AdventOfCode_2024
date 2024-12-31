# <p align="center">Advent of Code 2024 </p>
$${\color{yellow}*}$$
$${\color{green}>\color{orange}o\color{green}<}$$
$${\color{green}>\color{red}@\color{green}>\color{blue}O\color{green}<}$$
$${\color{green}>\color{blue}O\color{green}>\color{orange}o\color{green}<\color{red}@\color{green}<}$$
$${\color{brown}\\#\\#}$$
### <p align="center">50/50 Stars Obtained</p>

All of my C++ solutions for this year are compiled into this project.

Solutions are my own unless otherwise noted.

Concepts/Tools I have implemented include:

- Factory method design pattern: Each day's solution is a derived class from a parent Solution class, which has their own similarly derived factory/creator. The main() function loops through days, creating an instance of the day's solution class and executing a oneStarSolution() and twoStarSolution() member function, which imports the day's input file, finds the solution, and returns it as a string.
- Object Oriented Programming: Days 6, 14 (Classes were used for almost every solution, but these almost exclusively used member functions to solve the puzzle).
- Regular Expressions: Days 3, 4
- Rotating 2D Arrays: Day 4
- Recursion: Days 7, 10, 11, 15, 17, 18, 19, 21, 23
- Operator Overloading: Days 8, 12, 16, 20, 22
- Graph Data Structures: Days 10, 16
- Depth First Search: Days 10, 
- Breadth First Search (Queue Implementation): Days 16, 18
- Dynamic Programming / Memoization: Days 11, 15, 19, 21
- [Flood Fill Algorithm](https://en.wikipedia.org/wiki/Flood_fill): Days 12, 18 (Came up with it on my own on day 12, later found it had a name)
- Linear Algebra/[Cramer's Rule](https://en.wikipedia.org/wiki/Cramer%27s_rule): Day 13 (Received the high-level concept from the [AoC subreddit](https://www.reddit.com/r/adventofcode/), implemented it myself).
- [Chinese Remainder Theorem](https://en.wikipedia.org/wiki/Chinese_remainder_theorem): Day 14 (Initially solved myself, but without knowing how to evaluate two modulus equations for equality, I needed to brute-force some values to find a solution. Later learned about the chinese remainder theorem and inverse mod from Reddit user [i_have_no_biscuits](https://www.reddit.com/r/adventofcode/comments/1he0asr/comment/m1zzfsh/) and implemented the optimized solution.
- [Maximal Cliques](https://en.wikipedia.org/wiki/Clique_problem): Day 23

  
Notes:

- C++'s regex library is well known to be cumbersome and slows compilation significantly. Google has a regex library, RE2, which is supposed to be a much better implementaiton and I may refactor to it later.

- Day 1's two star solution has 3 sub-solutions using different data structures, as I was curious how they impacted time complexity. It is coded to use an unordered map, as it had the fastest average runtime, but there are also methods for solutions using a regular map (which has a red-black tree under the hood) or iterate through the arrays that were sorted for the one star solution.

## Why won't this run? Where are the puzzle_input files?

As per the AoC FAQ, 

>**Can I copy/redistribute part of Advent of Code?** Please don't. Advent of Code is free to use, not free to copy. If you're posting a code repository somewhere, please don't include parts of Advent of Code like the puzzle text or your inputs.

my puzzle inputs are not included. If you wish to test my solutions, feel free to visit https://adventofcode.com/2024/ and use your own puzzle inputs.
