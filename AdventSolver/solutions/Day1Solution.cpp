/** Dev: Dave West
 * Date: December 1, 2024
 * Desc: Method definitions for the AoC 2024 day 1 puzzle.
 *  Log: 12/ 1/2024 - Completed solution.
 *       12/ 4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/ 7/2024 - Refactored integer to long long or size_t.
 *                    Refactored puzzle parsing from regex to stringstream.
 *       12/17/2024 - Refactored one and two star solutions to return strings.
 *       12/19/2024 - Refactored two-star solution to use a switch-case in choosing a data structure to use.
 */

#include "Day1Solution.h"


Day1Solution::Day1Solution(const std::vector<std::string> & puzzleInput) {
    title = "--- Day 1: Historian Hysteria ---";

    splitList(puzzleInput);
    sort(leftList.begin(),  leftList.end());
    sort(rightList.begin(), rightList.end());
}


void Day1Solution::splitList(const vector<string> & inputList)
{
    for (const auto& line : inputList)
    {
        std::stringstream ss(line);

        size_t leftNumber, rightNumber;
        ss >> leftNumber >> rightNumber;;

        leftList.push_back(leftNumber);
        rightList.push_back(rightNumber);
    }
}


string Day1Solution::oneStarSolution() {
    // Calculate total distance
    long long answer {0};
    for (size_t i = 0; i < leftList.size(); i++)
        answer += abs(static_cast<int>(leftList[i] - rightList[i]));
    return std::to_string(answer);
}


string Day1Solution::twoStarSolution() {
    return std::to_string(solveTwoStarProblem(UNORDERED_MAP));
}


size_t Day1Solution::solveTwoStarProblem(const SolutionDataStructure &dataStructure)
{
    if (dataStructure == SORTED_LISTS)
        return twoStarsPreSortedLists();

    if (dataStructure == MAP)
        return twoStarsMap();

    if (dataStructure == UNORDERED_MAP)
        return twoStarsUnorderedMap();

    return 0;
}


/**
 * Implementation for the two-stars difficulty problem using a map.
 * O(n*m) to create rightListCounts, O(n log m) to calculate similarity score.
 * @return Returns the similarity score for the two lists.
 */
size_t Day1Solution::twoStarsMap()
{
    size_t similarityScore {0};
    // For a location ID in the right list(key), count the number of times it appears in the list (value)
    std::map<size_t,size_t> rightListCounts;
    for (auto locationID : rightList)
    {
        if (rightListCounts.contains(locationID))
            rightListCounts[locationID]++;
        else
            rightListCounts[locationID] = 1;
    }

    // Find the similarity score SUM(left list value * right list count)
    for (auto locationID : leftList)
        if (rightListCounts.contains(locationID))
            similarityScore += locationID * rightListCounts[locationID];
    // else add 0 (or don't for an unnoticeably minor optimization)

    return similarityScore;
}


/**
 * Implementation for the two-stars problem using pre-sorted lists.
 * O(m+n) -> Iterates through both lists once
 * @return
 */
size_t Day1Solution::twoStarsPreSortedLists()
{
    size_t similarityScore {0};

    int leftIndex = 0, rightIndex = 0;
    while (leftIndex < leftList.size() && rightIndex < rightList.size())
    {
        int rightCount = 0;

        while (leftList[leftIndex] == rightList[rightIndex])
        {
            rightCount++;
            rightIndex++;
        }
        similarityScore += leftList[leftIndex] * rightCount;

        while (leftList[leftIndex] < rightList[rightIndex] && leftIndex < leftList.size())
            leftIndex++;

        while (leftList[leftIndex] > rightList[rightIndex] && rightIndex < rightList.size())
            rightIndex++;
    }

    return similarityScore;
}


/**
 * Implementation for the two-stars problem using an unordered map.
 * O(n*m) to create rightListCounts, O(n) to calculate similarity score (assuming no collisions)
 * @return
 */
size_t Day1Solution::twoStarsUnorderedMap()
{
    size_t similarityScore {0};
    // For a location ID in the right list(key), count the number of times it appears in the list (value)
    std::unordered_map<size_t,size_t> rightListCounts;
    for (auto locationID : rightList)
    {
        if (rightListCounts.contains(locationID))
            rightListCounts[locationID]++;
        else
            rightListCounts[locationID] = 1;
    }

    // Find the similarity score SUM(left list value * right list count)
    for (auto locationID : leftList)
        if (rightListCounts.contains(locationID))
            similarityScore += locationID * rightListCounts[locationID];
    // else add 0 (or don't for an unnoticeably minor optimization)

    return similarityScore;
}