
#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <memory>
#include <vector>

using std::vector, std::string;

// Abstract Product class
class Solution {
    enum difficulty {oneStar, twoStars};

public:
    virtual ~Solution() = default;
    [[nodiscard]] virtual string getTitle() const = 0;

    virtual string oneStarSolution() = 0;
    virtual string twoStarSolution() = 0;
};

#endif //SOLUTION_H
