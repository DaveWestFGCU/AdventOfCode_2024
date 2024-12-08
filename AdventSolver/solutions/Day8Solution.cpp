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
    for (auto firstAntenna_it = antennaLocations.begin(); firstAntenna_it != antennaLocations.end(); ++firstAntenna_it)
        for (auto secondAntenna_it = firstAntenna_it+1; secondAntenna_it != antennaLocations.end(); ++secondAntenna_it)
        {
            const int firstAntennaY = static_cast<int>(firstAntenna_it->y);
            const int secondAntennaY = static_cast<int>(secondAntenna_it->y);
            const int yDifference = abs(firstAntennaY - secondAntennaY);

            const int firstAntennaX = static_cast<int>(firstAntenna_it->x);
            const int secondAntennaX = static_cast<int>(secondAntenna_it->x);
            const int xDifference = abs(firstAntennaX - secondAntennaX);

            if (firstAntennaY > secondAntennaY && firstAntennaX > secondAntennaX)
            {   //  First antenna below-right of second antenna
                Pos antinodePosition(firstAntennaY + yDifference, firstAntennaX + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntennaY + yDifference,firstAntennaX + xDifference));
                    std::cout << "Antinode: (" << firstAntennaY + yDifference << ", "
                    << firstAntennaX + xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntennaY - yDifference, secondAntennaX - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntennaY - yDifference, secondAntennaX - xDifference));
                    std::cout << "Antinode: (" << secondAntennaY - yDifference
                              << ", " << secondAntennaX - xDifference << ")" << std::endl;
                }
            }

            else if (firstAntennaY > secondAntennaY && firstAntennaX < secondAntennaX)
            {   //  First antenna below-left of second antenna
                Pos antinodePosition(firstAntennaY + yDifference, firstAntennaX - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntennaY + yDifference, firstAntennaX - xDifference));
                    std::cout << "Antinode: (" << firstAntennaY + yDifference
                              << ", " << firstAntennaX - xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntennaY - yDifference, secondAntennaX + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntennaY - yDifference, secondAntennaX + xDifference));
                    std::cout << "Antinode: (" << secondAntennaY - yDifference
                              << ", " << secondAntennaX + xDifference << ")" << std::endl;
                }
            }

            else if (firstAntennaY < secondAntennaY && firstAntennaX > secondAntennaX)
            {   //  First antenna above-right of second antenna
                Pos antinodePosition(firstAntennaY - yDifference, firstAntennaX + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntennaY - yDifference, firstAntennaX + xDifference));
                    std::cout << "Antinode: (" << firstAntennaY - yDifference
                              << ", " << firstAntennaX + xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntennaY + yDifference, secondAntennaX - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntennaY + yDifference, secondAntennaX - xDifference));
                    std::cout << "Antinode: (" << secondAntennaY + yDifference
                              << ", " << secondAntennaX - xDifference << ")" << std::endl;
                }
            }

            else
            {   //  First antenna above-left of second antenna
                Pos antinodePosition(firstAntennaY - yDifference, firstAntennaX - xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(firstAntennaY - yDifference, firstAntennaX - xDifference));
                    std::cout << "Antinode: (" << firstAntennaY - yDifference
                              << ", " << firstAntennaX - xDifference << ")" << std::endl;
                }

                antinodePosition = Pos(secondAntennaY + yDifference, secondAntennaX + xDifference);
                if (isInBounds(antinodePosition))
                {
                    antinodeLocations.insert(Pos(secondAntennaY + yDifference, secondAntennaX + xDifference));
                    std::cout << "Antinode: (" << secondAntennaY + yDifference
                              << ", " << secondAntennaX + xDifference << ")" << std::endl;
                }
            }
        }
}


bool Day8Solution::isInBounds(Pos antinodePosition)
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

