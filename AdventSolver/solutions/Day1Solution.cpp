

#include "Day1Solution.h"


Day1Solution::Day1Solution(const std::vector<std::string> & puzzleInput) {
    title = "--- Day 1: Historian Hysteria ---";

    splitList(puzzleInput, leftList, rightList);
    sort(leftList.begin(),  leftList.end());
    sort(rightList.begin(), rightList.end());
}


int Day1Solution::oneStarSolution() {
    // Calculate total distance
    int answer {0};
    for (size_t i = 0; i < leftList.size(); i++)
        answer += abs(leftList[i] - rightList[i]);
    return answer;
}


void Day1Solution::splitList(const vector<string> & inputList, vector<int> & leftList, vector<int> & rightList)
{
    const std::regex pattern(R"(\b\d+\b)");

    for (auto const& line : inputList)
    {
        std::sregex_iterator matches(line.begin(), line.end(), pattern);

        leftList.push_back(stoi(matches->str()));
        rightList.push_back(stoi((++matches)->str()));
    }
}


int Day1Solution::twoStarSolution() {
    return twoStarsUnorderedMap(leftList, rightList);
}


std::string Day1Solution::getTitle() const {
    return title;
}


/**
 * Implementation for the two-stars difficulty problem using a map.
 * O(n*m) to create rightListCounts, O(n log m) to calculate similarity score.
 * @param leftList
 * @param rightList
 * @return Returns the similarity score for the two lists.
 */
int Day1Solution::twoStarsMap(const vector<int> & leftList, const vector<int> & rightList)
{
    int similarityScore {0};
    // For a location ID in the right list(key), count the number of times it appears in the list (value)
    std::map<int,int> rightListCounts;
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
 * @param leftList
 * @param rightList
 * @return
 */
int Day1Solution::twoStarsPreSortedLists(const vector<int> & leftList, const vector<int> & rightList)
{
    int similarityScore {0};

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
 * @param leftList
 * @param rightList
 * @return
 */
int Day1Solution::twoStarsUnorderedMap(const vector<int> & leftList, const vector<int> & rightList)
{
    int similarityScore {0};
    // For a location ID in the right list(key), count the number of times it appears in the list (value)
    std::unordered_map<int,int> rightListCounts;
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