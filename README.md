# Advent of Code 2024

All of my C++ solutions for this year are compiled into this project.

Solutions are my own unless otherwise noted.

Concepts/Tools I have implemented thus far include:

- Factory method design pattern (each day is a concrete product with an overriding method for each solution).
  
- Regular Expressions (Days 3 & 4)
  
- Maps (Day 1 second-star)

- Recursion (Day 7)

Notes:

- C++'s regex library is well known to be cumbersome and slows compilation significantly. Google has a regex library, RE2, which is supposed to be a much better implementaiton and I may refactor to it later.

- Day 1's two star solution has 3 sub-solutions using different data structures, as I was curious how they impacted time complexity. It is coded to use an unordered map, as it had the fastest average runtime, but there are also methods for solutions using a regular map (which has a red-black tree under the hood) or iterate through the arrays that were sorted for the one star solution.

## Why won't this run? Where are the puzzle_input files?

As per the AoC FAQ, 

>**Can I copy/redistribute part of Advent of Code?** Please don't. Advent of Code is free to use, not free to copy. If you're posting a code repository somewhere, please don't include parts of Advent of Code like the puzzle text or your inputs.

my puzzle inputs are not included. If you wish to test my solutions, feel free to visit https://adventofcode.com/2024/ and use your own puzzle inputs.
