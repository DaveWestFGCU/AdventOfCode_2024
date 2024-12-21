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
    for (int button1 = 0; button1 <= A; ++button1)
        for (int button2 = 0; button2 <= A; ++button2)
        {
            char button1Char = button1 == A ? 'A' : static_cast<char>(button1 + '0');
            char button2Char = button2 == A ? 'A' : static_cast<char>(button2 + '0');
            numKeyLookup[{button1Char,button2Char}] = numKeysToDirectionKeys(buttonPosition[button1Char], buttonPosition[button2Char]);
        }
}


string Day21Solution::numKeysToDirectionKeys(Position button1, Position button2)
{
    string translation;
    int xDistance = button2.x - button1.x;
    int yDistance = button2.y - button1.y;

    // Avoid the empty space
    if (button1.y == 0 && button2.x == 0)
    {
        for (int y = 0; y < yDistance; ++y)
            translation += "^";

        for (int x = 0; x > xDistance; --x)
            translation += "<";

        return translation + "A";
    }

    // Avoid the empty space
    if (button1.x == 0 && button2.y == 0)
    {
        for (int y = 0; y > yDistance; --y)
            translation += ">";

        for (int x = 0; x < xDistance; ++x)
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
    for (int button1 = LEFT; button1 <= ACT; ++button1)
        for (int button2 = LEFT; button2 <= ACT; ++button2)
            directionLookup[{buttonNum[button1], buttonNum[button2]}] = numKeysToDirectionKeys(buttonPosition[buttonNum[button1]], buttonPosition[buttonNum[button2]]);
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


string Day21Solution::translateDirectionToDirections(const char &fromKey, const char &toKey, const int &depth)
{
    // Base case: No more translating
    if (depth == 0)
        return {toKey};

    // Recursive case: Apply translation, go a layer deeper
    string directions = directionLookup[{fromKey, toKey}];

    string newDirections;
    for (int i = 0; i < directions.length(); ++i)
    {
        char startButton = (i == 0) ? 'A' : directions[i-1];
        char endButton = directions[i];

        newDirections += translateDirectionToDirections(startButton, endButton, depth-1);
    }

    return newDirections;
}


string Day21Solution::oneStarSolution()
{
    int directionalKeypads = 2;
    int sumComplexities { 0 };

    for (const auto &code : doorCodes)
    {
        string firstDirections = codeToDirections(code);

        string newCode;
        for (int i = 0; i < firstDirections.length(); ++i)
        {
            if (i == 0)
                newCode += translateDirectionToDirections('A', firstDirections[i], directionalKeypads);
            else
                newCode += translateDirectionToDirections(firstDirections[i-1], firstDirections[i], directionalKeypads);
        }

        int codeLength = newCode.length();
        int codeNum = std::stoi(code.substr(0,code.length()-1));
        sumComplexities += codeLength * codeNum;
    }

    return std::to_string(sumComplexities);
}


string Day21Solution::twoStarSolution()
{
    return "Not yet implemented.";
}
