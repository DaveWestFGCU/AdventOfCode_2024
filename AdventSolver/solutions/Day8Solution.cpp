/*  Dev: Dave West
 * Date: December 8, 2024
 * Desc: Method definitions for the AoC 2024 day 8 puzzle.
 */

#include "Day8Solution.h"


Day8Solution::Day8Solution(const vector<string> &puzzleInput)
    : title("--- Day 8: Resonant Collinearity ---"),
      mapBounds(Pos{static_cast<int>(puzzleInput.size()), static_cast<int>(puzzleInput[0].length())})
{
    buildAntennaPositionLists(puzzleInput);
    printFrequencies();
}


void Day8Solution::buildAntennaPositionLists(const vector<string> &puzzleInput)
{
    for (size_t row = 0; row < mapBounds.y; row++)
    {
        for (size_t col = 0; col < mapBounds.x; col++)
        {
            char letter = puzzleInput[row][col];
            if (letter == '.')  // '.' is empty space
                continue;

            frequencyToAntennaLocations[letter].emplace_back(row,col);
        }
    }
}


void Day8Solution::printFrequencies()
{
    for (const auto &[frequency, positions] : frequencyToAntennaLocations)
    {
        std::cout << "Key: " << frequency << ", Value: ";
        for (const auto &[y, x] : positions)
        {
            std::cout << "(" << y << ", " << x << "), ";
        }
        std::cout << std::endl;
    }
}


long long Day8Solution::oneStarSolution()
{
    for (const auto &[frequency, antennaPositions] : frequencyToAntennaLocations)
    {
        findAntinodes(antennaPositions);
    }
    return static_cast<long long>(antinodeLocations.size());
}


void Day8Solution::findAntinodes(const vector<Pos> &antennaLocations)
{
    for (auto firstAntenna = antennaLocations.begin(); firstAntenna != antennaLocations.end(); ++firstAntenna)
        for (auto secondAntenna = firstAntenna+1; secondAntenna != antennaLocations.end(); ++secondAntenna)
        {
            const int yDifference = abs(firstAntenna->y - secondAntenna->y);

            const int xDifference = abs(firstAntenna->x - secondAntenna->x);

            if (firstAntenna->isBelow(*secondAntenna) && firstAntenna->isRightOf(*secondAntenna))
            {
                Pos antinodePosition(firstAntenna->y + yDifference, firstAntenna->x + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntenna->y + yDifference,firstAntenna->x + xDifference));
                    std::cout << "Antinode: (" << firstAntenna->y + yDifference << ", "
                    << firstAntenna->x + xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntenna->y - yDifference, secondAntenna->x - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntenna->y - yDifference, secondAntenna->x - xDifference));
                    std::cout << "Antinode: (" << secondAntenna->y - yDifference
                              << ", " << secondAntenna->x - xDifference << ")" << std::endl;
                }
            }

            else if (firstAntenna->isBelow(*secondAntenna) && firstAntenna->isLeftOf(*secondAntenna))
            {
                Pos antinodePosition(firstAntenna->y + yDifference, firstAntenna->x - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntenna->y + yDifference, firstAntenna->x - xDifference));
                    std::cout << "Antinode: (" << firstAntenna->y + yDifference
                              << ", " << firstAntenna->x - xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntenna->y - yDifference, secondAntenna->x + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntenna->y - yDifference, secondAntenna->x + xDifference));
                    std::cout << "Antinode: (" << secondAntenna->y - yDifference
                              << ", " << secondAntenna->x + xDifference << ")" << std::endl;
                }
            }

            else if (firstAntenna->isAbove(*secondAntenna) && firstAntenna->isRightOf(*secondAntenna))
            {
                Pos antinodePosition(firstAntenna->y - yDifference, firstAntenna->x + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntenna->y - yDifference, firstAntenna->x + xDifference));
                    std::cout << "Antinode: (" << firstAntenna->y - yDifference
                              << ", " << firstAntenna->x + xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntenna->y + yDifference, secondAntenna->x - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntenna->y + yDifference, secondAntenna->x - xDifference));
                    std::cout << "Antinode: (" << secondAntenna->y + yDifference
                              << ", " << secondAntenna->x - xDifference << ")" << std::endl;
                }
            }

            else
            {   //  First antenna above-left of second antenna
                Pos antinodePosition(firstAntenna->y - yDifference, firstAntenna->x - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntenna->y - yDifference, firstAntenna->x - xDifference));
                    std::cout << "Antinode: (" << firstAntenna->y - yDifference
                              << ", " << firstAntenna->x - xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntenna->y + yDifference, secondAntenna->x + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntenna->y + yDifference, secondAntenna->x + xDifference));
                    std::cout << "Antinode: (" << secondAntenna->y + yDifference
                              << ", " << secondAntenna->x + xDifference << ")" << std::endl;
                }
            }
        }
}


bool Day8Solution::isInBounds(Pos antinodePosition) const
{
    if (0 <= antinodePosition.x && antinodePosition.x < mapBounds.x)
        if (0 <= antinodePosition.y && antinodePosition.y < mapBounds.y)
            return true;

    return false;
}


long long Day8Solution::twoStarSolution()
{
    int result {0};

    return result;
}

