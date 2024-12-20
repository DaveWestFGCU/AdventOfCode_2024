/** Dev: Dave West
 * Date: December 20, 2024
 * Desc: Method definitions for the AoC 2024 day 20 puzzle.
 */

#include "Day20Solution.h"


Day20Solution::Day20Solution(const vector<string> &puzzleInput)
    : title("--- Day 20: Race Condition ---")
{
    racetrack = puzzleInput;
    parseTrack();
    runTrack();
}


void Day20Solution::parseTrack()
{
    for (int y = 1; y < racetrack.size()-1; y++)
    {
        for (int x = 1; x < racetrack[y].length()-1; x++)
        {
            switch (racetrack[y][x])
            {
                case '#':
                    walls.emplace_back(x,y);
                    continue;

                case 'S':
                    startPosition = Position(x,y);
                    racetrack[y][x] = '.';
                    continue;

                case 'E':
                    endPosition = Position(x,y);
                    racetrack[y][x] = '.';
                    continue;

                case '.':
                    continue;

                default:
                    std::cerr << "Unknown tile: ";
                    std::cout << racetrack[y][x] << std::endl;
            }
        }
    }
}


void Day20Solution::runTrack()
{
    Position currentPosition = startPosition;
    Position lastPosition = startPosition;
    int step {0};

    while (currentPosition != endPosition)
    {
        track[currentPosition] = step;
        Position nextPosition = findNextPosition(currentPosition, lastPosition);

        lastPosition = currentPosition;
        currentPosition = nextPosition;

        step++;
    }
    track[currentPosition] = step;
    // std::cout << "End position reached! " << track[currentPosition] << " steps" << std::endl;
}


void Day20Solution::printSteps()
{
    for (int y = 0; y < racetrack.size(); y++)
    {
        for (int x = 0; x < racetrack[y].length(); x++)
        {
            if (racetrack[y][x] == '.')
                std::cout << track[{x,y}] % 10;
            else
                std::cout << racetrack[y][x];
        }
        std::cout << std::endl;
    }
}


Day20Solution::Position Day20Solution::findNextPosition(const Position &current, const Position &last)
{
    // NORTH
    if (racetrack[current.y-1][current.x] == '.' && Position(current.x, current.y-1) != last)
        return {current.x, current.y-1};

    // EAST
    if (racetrack[current.y][current.x+1] == '.' && Position(current.x+1, current.y) != last)
        return {current.x+1, current.y};

    // SOUTH
    if (racetrack[current.y+1][current.x] == '.' && Position(current.x, current.y+1) != last)
        return {current.x, current.y+1};

    // WEST
    if (racetrack[current.y][current.x-1] == '.' && Position(current.x-1, current.y) != last)
        return {current.x-1, current.y};

    std::cout << "SHOULDN'T BE HERE" << std::endl;
    return {-1,-1};
}



string Day20Solution::oneStarSolution()
{
    int minTimeSaved {1};
    if (track[endPosition] > 100)
        minTimeSaved = 100;

    int bestCheatCount {0};
    for (const auto wall : walls)
    {
        int timeSaved = getTimeSaved(wall);
        if (timeSaved >= minTimeSaved)
            bestCheatCount++;
    }

    return std::to_string(bestCheatCount);
}


int Day20Solution::getTimeSaved(Position wall)
{
    std::vector<Position> neighborTracks;
    // NORTH
    if (racetrack[wall.y-1][wall.x] == '.')
        neighborTracks.emplace_back(wall.x, wall.y-1);

    // EAST
    if (racetrack[wall.y][wall.x+1] == '.')
        neighborTracks.emplace_back(wall.x+1, wall.y);

    // SOUTH
    if (racetrack[wall.y+1][wall.x] == '.')
        neighborTracks.emplace_back(wall.x, wall.y+1);

    // WEST
    if (racetrack[wall.y][wall.x-1] == '.')
        neighborTracks.emplace_back(wall.x-1, wall.y);

    if (neighborTracks.size() < 2) // Removing the wall does not make a short-cut.
        return 0;

    if (neighborTracks.size() > 2)  //  Last segment of wall.
        return 2;

    int difference = std::abs(track[neighborTracks[0]] - track[neighborTracks[1]]);

    return difference - 2;
}


string Day20Solution::twoStarSolution()
{
    int result {0};

    return std::to_string(result);
}
