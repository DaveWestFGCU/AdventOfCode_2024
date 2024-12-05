# Advent of Code 2024

All of my C++ solutions for this year are compiled into this project.

Solutions are geared towards praticing tools and patterns that I want to learn or reinforce, and not necessarily the quickest implementation or most optimal runtime.

Concepts/Tools I have implemented thus far include:

- Factory method design pattern (AoCSolver being the concrete creator and each day's solutions being the concrete products).
- Regular Expressions (Whenver possible. I just think they're neat!)
- Maps/Unordered Maps (Day 1 Star Two Solution)

Notes:
- C++'s regex library is well known to be cumbersome and slows compilation significantly. Google has a regex library, RE2, which is supposed to be a much better implementaiton and I may implement it later.
- Day 1's Two Star solution has 3 solutions. It is coded to use an unordered map, as it had the fastest average runtime, but there are also methods for an ordered map and presorted array solution.

## Why won't this run? Where are the puzzle_input files?

As per the AoC FAQ, 

>**Can I copy/redistribute part of Advent of Code?** Please don't. Advent of Code is free to use, not free to copy. If you're posting a code repository somewhere, please don't include parts of Advent of Code like the puzzle text or your inputs.

my puzzle inputs are not included. If you wish to test my solutions, feel free to visit http://adventofcode.com/2024/ and get your own puzzle inputs.
