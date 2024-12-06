
#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <memory>
#include <vector>

// Abstract Product class
class Solution {
    enum difficulty {oneStar, twoStars};

public:
    virtual ~Solution() = default;
    virtual std::string getTitle() const = 0;
    virtual long long oneStarSolution() = 0;
    virtual long long twoStarSolution() = 0;
};

#endif //SOLUTION_H
