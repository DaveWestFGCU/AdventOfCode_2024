/** Dev: Dave West
 * Date: December 21, 2024
 * Desc: Method definitions for the AoC 2024 day 21 puzzle.
 */

#include "Day21Solution.h"


Day21Solution::Day21Solution(const vector<string> &puzzleInput)
    : title("--- Day 21: Keypad Conundrum ---"), numKeyLookup(), directionLookup()
{
    this->doorCodes = puzzleInput;
    buildNumberToDirectionLookup();
    buildDirectionToDirectionLookup();
}


void Day21Solution::buildNumberToDirectionLookup()
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


string Day21Solution::numKeysToDirectionKeys(Position fromKey, Position toKey)
{
    string translation;
    int xDistance = toKey.x - fromKey.x;
    int yDistance = toKey.y - fromKey.y;

    // Avoid the empty space
    if (fromKey.y == 0 && toKey.x == 0)
    {
        for (int y = 0; y < yDistance; ++y)
            translation += "^";

        for (int x = 0; x > xDistance; --x)
            translation += "<";

        return translation + "A";
    }

    // Avoid the empty space
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


void Day21Solution::buildDirectionToDirectionLookup()
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


string Day21Solution::directionKeysToDirectionKeys(Position fromKey, Position toKey)
{
    string translation;
    int xDistance = toKey.x - fromKey.x;
    int yDistance = toKey.y - fromKey.y;

    // Avoid the empty space
    if (fromKey.y == 1 && toKey.x == 0)
    {
        for (int y = 0; y > yDistance; --y)
            translation += "v";

        for (int x = 0; x > xDistance; --x)
            translation += "<";

        return translation + "A";
    }

    // Avoid the empty space
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

string Day21Solution::codeToDirections(const string &code)
{
    string directions;
    for (int i = 0; i < code.length(); ++i)
    {
        char startButton = (i == 0) ? 'A' : code[i-1];
        char endButton = code[i];

        directions += numKeyLookup[{startButton,endButton}];
    }

    return directions;
}


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


string Day21Solution::oneStarSolution()
{
    int directionalKeypads = 2;
    long long sumComplexities { 0 };

    for (const auto &code : doorCodes)
    {
        string firstDirections = codeToDirections(code);

        long long codeLength { 0 };
        for (int i = 0; i < firstDirections.length(); ++i)
        {
            if (i == 0)
                codeLength = translateDirectionToDirections('A', firstDirections[i], directionalKeypads);
            else
                codeLength += translateDirectionToDirections(firstDirections[i-1], firstDirections[i], directionalKeypads);
        }
        int codeNum = std::stoi(code.substr(0,code.length()-1));
        sumComplexities += codeLength * codeNum;
    }

    return std::to_string(sumComplexities);
}


string Day21Solution::twoStarSolution()
{
    int directionalKeypads = 25;
    long long sumComplexities { 0 };

    for (const auto &code : doorCodes)
    {
        string firstDirections = codeToDirections(code);

        long long codeLength { 0 };
        for (int i = 0; i < firstDirections.length(); ++i)
        {
            if (i == 0)
                codeLength = translateDirectionToDirections('A', firstDirections[i], directionalKeypads);
            else
                codeLength += translateDirectionToDirections(firstDirections[i-1], firstDirections[i], directionalKeypads);
        }
        int codeNum = std::stoi(code.substr(0,code.length()-1));
        sumComplexities += codeLength * codeNum;
    }

    return std::to_string(sumComplexities);
}
