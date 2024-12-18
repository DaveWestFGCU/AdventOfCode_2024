/** Dev: Dave West
 * Date: December 1, 2024
 * Desc: Method definitions for the AoC 2024 day 1 puzzle.
 *  Log: 12/ 1/2024 - Completed solution.
 *       12/ 4/2024 - Refactored from its own program to a class for a larger solutions program.
 *       12/ 7/2024 - Refactored integer to long long or size_t.
 *                    Refactored puzzle parsing from regex to stringstream.
 *       12/17/2024 - Refactored one and two star solutions to return strings.
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
    return std::to_string(twoStarsUnorderedMap());
}


std::string Day1Solution::getTitle() const {
    return title;
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

    int i = 0, j = 0;
    while (i < leftList.size() && j < rightList.size())
    {
        int rightCount = 0;

        while (leftList[i] == rightList[j])
        {
            rightCount++;
            j++;
        }
        similarityScore += leftList[i] * rightCount;

        while (leftList[i] < rightList[j] && i < leftList.size())
            i++;

        while (leftList[i] > rightList[j] && j < rightList.size())
            j++;
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