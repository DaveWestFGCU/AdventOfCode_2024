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
        findFrequencyAntinodes(antennaPositions);

    return static_cast<long long>(antinodeLocations.size());
}


void Day8Solution::findFrequencyAntinodes(const vector<Pos> &antennaLocations, bool includeHarmonics)
{
    for (auto firstAntenna = antennaLocations.begin(); firstAntenna != antennaLocations.end(); ++firstAntenna)
        for (auto secondAntenna = antennaLocations.begin(); secondAntenna != antennaLocations.end(); ++secondAntenna)
        {
            if (firstAntenna == secondAntenna)
                continue;

            if (includeHarmonics)
                findAntennaAntinodes(*firstAntenna, *secondAntenna, includeHarmonics);
            else
                findAntennaAntinodes(*firstAntenna, *secondAntenna);
        }
}


void Day8Solution::findAntennaAntinodes(const Pos &firstAntenna, const Pos &secondAntenna, const bool findHarmonics, const size_t harmonicNumber)
{
    // Get the x and y coordinates for a point on a line with antenna 1 and 2, but with a scalar applied to the distance
    const int antinodeX = static_cast<int>(secondAntenna.x + harmonicNumber * (secondAntenna.x - firstAntenna.x));
    const int antinodeY = static_cast<int>(secondAntenna.y + harmonicNumber * (secondAntenna.y - firstAntenna.y));

    Pos antinode(antinodeY, antinodeX);
    if (isInBounds(antinode))
    {
        antinodeLocations.insert(antinode);

        if (findHarmonics)
            findAntennaAntinodes(firstAntenna, secondAntenna, findHarmonics, harmonicNumber+1);
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
    for (const auto &[frequency, antennaPositions] : frequencyToAntennaLocations)
        findFrequencyAntinodes(antennaPositions, true);

        // Include antinodes on top of every antenna
    addAntennaAntinodes();

    return static_cast<long long>(antinodeLocations.size());
}


void Day8Solution::addAntennaAntinodes()
{
    for (const auto &[frequency, antennaPositions] : frequencyToAntennaLocations)
        for (const auto &[y,x] : antennaPositions)
            antinodeLocations.emplace(y,x);
}
