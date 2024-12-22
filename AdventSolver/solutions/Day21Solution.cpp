/** Dev: Dave West
 * Date: December 21, 2024
 * Desc: Method definitions for the AoC 2024 day 21 puzzle.
 */

#include "Day21Solution.h"

/**
 * Parses the day's input and builds lookups for memoization later.
 * @param puzzleInput
 */
Day21Solution::Day21Solution(const vector<string> &puzzleInput)
    : title("--- Day 21: Keypad Conundrum ---")
{
    this->doorCodes = puzzleInput;
    buildNumKeyLookup();
    buildDirectionLookup();
}


/**
 * Fills the numKeyLookup member variable with the shortest path between any two buttons on the number keypad.
 * We're going to do a lot of these, so might as well memoize it for later.
 */
void Day21Solution::buildNumKeyLookup()
{
    std::unordered_map<char,Position> buttonPosition;
    buttonPosition['0'] = {1,0};
    buttonPosition['1'] = {0,1};
    buttonPosition['2'] = {1,1};
    buttonPosition['3'] = {2,1};
    buttonPosition['4'] = {0,2};
    buttonPosition['5'] = {1,2};
    buttonPosition['6'] = {2,2};
    buttonPosition['7'] = {0,3};
    buttonPosition['8'] = {1,3};
    buttonPosition['9'] = {2,3};
    buttonPosition['A'] = {2,0};

    // The Manhattan Distance between two points (X1, Y1) and (X2, Y2) is given by |X1 – X2| + |Y1 – Y2|.
    for (int fromKey = 0; fromKey <= A; ++fromKey)
        for (int toKey = 0; toKey <= A; ++toKey)
        {
            char fromKeyChar = fromKey == A ? 'A' : static_cast<char>(fromKey + '0');
            char toKeyChar = toKey == A ? 'A' : static_cast<char>(toKey + '0');
            numKeyLookup[{fromKeyChar,toKeyChar}] = numKeysToDirectionKeys(buttonPosition[fromKeyChar], buttonPosition[toKeyChar]);
        }
}


/**
 * Finds the shortest path between two num keys based on their position.
 * @param fromKey Button position at the start of the movement.
 * @param toKey Button position at the end of the movement.
 * @return Returns a string of the arrow keys for the shortest path.
 */
string Day21Solution::numKeysToDirectionKeys(Position fromKey, Position toKey)
{
    string translation;
    int xDistance = toKey.x - fromKey.x;
    int yDistance = toKey.y - fromKey.y;

    // Avoid the empty space @ (0,0)
    if (fromKey.y == 0 && toKey.x == 0)
    {
        for (int y = 0; y < yDistance; ++y)
            translation += "^";

        for (int x = 0; x > xDistance; --x)
            translation += "<";

        return translation + "A";
    }

    // Avoid the empty space @ (0,0)
    if (fromKey.x == 0 && toKey.y == 0)
    {
        for (int x = 0; x < xDistance; ++x)
            translation += ">";

        for (int y = 0; y > yDistance; --y)
            translation += "v";

        return translation + "A";
    }

    // Do the most expensive operation first
    for (int x = 0; x > xDistance; --x)
        translation += "<";

    for (int y = 0; y > yDistance; --y)
        translation += "v";

    for (int y = 0; y < yDistance; ++y)
        translation += "^";

    for (int x = 0; x < xDistance; ++x)
        translation += ">";

    return translation + "A";
}


/**
 * Fills the directionLookup member variable with the shortest path between any two buttons on the directional keypad.
 * We're going to do a lot of these, so might as well memoize it first.
 */
void Day21Solution::buildDirectionLookup()
{
    std::unordered_map<char,Position> buttonPosition;
    char buttonNum[5] = {'<', 'v', '>', '^', 'A'};
    buttonPosition['<'] = {0,0};
    buttonPosition['v'] = {1,0};
    buttonPosition['>'] = {2,0};
    buttonPosition['^'] = {1,1};
    buttonPosition['A'] = {2,1};

    // The Manhattan Distance between two points (X1, Y1) and (X2, Y2) is given by |X1 – X2| + |Y1 – Y2|.
    for (int fromKey = LEFT; fromKey <= ACT; ++fromKey)
        for (int toKey = LEFT; toKey <= ACT; ++toKey)
            directionLookup[{buttonNum[fromKey], buttonNum[toKey]}] = directionKeysToDirectionKeys(buttonPosition[buttonNum[fromKey]], buttonPosition[buttonNum[toKey]]);
}


/**
 * Finds the shortest path between two directional keys based on their position.
 * @param fromKey Button position at the start of the movement.
 * @param toKey Button position at the end of the movement.
 * @return Returns a string of the arrow keys for the shortest path.
 */
string Day21Solution::directionKeysToDirectionKeys(Position fromKey, Position toKey)
{
    string translation;
    int xDistance = toKey.x - fromKey.x;
    int yDistance = toKey.y - fromKey.y;

    // Avoid the empty space @ (0,1)
    if (fromKey.y == 1 && toKey.x == 0)
    {
        for (int y = 0; y > yDistance; --y)
            translation += "v";

        for (int x = 0; x > xDistance; --x)
            translation += "<";

        return translation + "A";
    }

    // Avoid the empty space @ (0,1)
    if (fromKey.x == 0 && toKey.y == 1)
    {
        for (int x = 0; x < xDistance; ++x)
            translation += ">";

        for (int y = 0; y < yDistance; ++y)
            translation += "^";

        return translation + "A";
    }

    // Do the most expensive operation first
    for (int x = 0; x > xDistance; --x)
        translation += "<";

    for (int y = 0; y > yDistance; --y)
        translation += "v";

    for (int y = 0; y < yDistance; ++y)
        translation += "^";

    for (int x = 0; x < xDistance; ++x)
        translation += ">";

    return translation + "A";
}


/**
 * Converts the initial code into the first set of directions.
 * @param code One line from the puzzle input.
 * @return A string of directions that will input the code.
 */
string Day21Solution::codeToDirections(const string &code)
{
    string directions;
    for (int i = 0; i < code.length(); ++i)
    {
        char startButton = (i == 0) ? 'A' : code[i-1];  //  Starts at 'A' position.
        char endButton = code[i];

        directions += numKeyLookup[{startButton,endButton}];
    }

    return directions;
}


/**
 * Recursive method for creating a directional input for the prior layer's directional input.
 * Uses tabulation to early return if we've calculated this start/end key pair and depth before.
 * @param fromKey Directional key to start from.
 * @param toKey Directional key to end at.
 * @param depth Depth of the translation. A directional input for a directional input for...
 * @return Returns the number of inputs at the depth of translation.
 */
long long Day21Solution::translateDirectionToDirections(const char &fromKey, const char &toKey, const int &depth)
{
    // Base case: No more translating
    if (depth == 0)
        return 1;

    // Base case: We've seen this movement at this depth before
    if (cache.contains({{fromKey,toKey},depth}))
        return cache[{{fromKey,toKey},depth}];

    // Recursive case: Apply translation, go a layer deeper
    string directions = directionLookup[{fromKey, toKey}];

    long long sequenceLength { 0 };
    for (int i = 0; i < directions.length(); ++i)
    {
        char startButton = (i == 0) ? 'A' : directions[i-1];
        char endButton = directions[i];

        sequenceLength += translateDirectionToDirections(startButton, endButton, depth-1);
    }

    cache[{{fromKey,toKey},depth}] = sequenceLength;
    return sequenceLength;
}


/**
 * Solution to the one-star problem.
 * @return Returns an appropriately formatted string of the solution.
 */
string Day21Solution::oneStarSolution()
{
    int directionalKeypads { 2 };
    long long sumComplexities { 0 };

    for (const auto &code : doorCodes)
    {
        long long numKeyPresses = calcCodeKeyPresses(code, directionalKeypads);
        int codeNum = std::stoi(code.substr(0,code.length()-1));
        sumComplexities += numKeyPresses * codeNum;
    }

    return std::to_string(sumComplexities);
}


/**
 * Finds the number of key pad presses needed at the first directional keypad to input the code at the numeric keypad.
 * @param initialCode One numeric door code from the puzzle input.
 * @param totalDepth Number of directional keypads.
 * @return Returns the number of key presses at the most distal directional keypad needed for the numeric keypad input.
 */
long long Day21Solution::calcCodeKeyPresses(const string &initialCode, const int &totalDepth)
{
    string firstDirections = codeToDirections(initialCode);

    long long numKeyPresses { 0 };
    for (int i = 0; i < firstDirections.length(); ++i)
    {
        if (i == 0)
            numKeyPresses = translateDirectionToDirections('A', firstDirections[i], totalDepth);
        else
            numKeyPresses += translateDirectionToDirections(firstDirections[i-1], firstDirections[i], totalDepth);
    }

    return numKeyPresses;
}


/**
 * Solution to the two-star problem.
 * @return Returns an appropriately formatted string of the solution.
 */
string Day21Solution::twoStarSolution()
{
    int directionalKeypads { 25 };
    long long sumComplexities { 0 };

    for (const auto &code : doorCodes)
    {
        long long numKeyPresses = calcCodeKeyPresses(code, directionalKeypads);
        int codeNum = std::stoi(code.substr(0,code.length()-1));
        sumComplexities += numKeyPresses * codeNum;
    }

    return std::to_string(sumComplexities);
}
