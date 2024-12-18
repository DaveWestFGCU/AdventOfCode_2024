/** Dev: Dave West
 * Date: December 9, 2024
 * Desc: Method definitions for the AoC 2024 day 9 puzzle.
 *  Log: 12/17/2024 - Refactored one and two-star solutions to return strings.
 */

#include "Day9Solution.h"


Day9Solution::Day9Solution(const vector<string> &puzzleInput)
    : title("--- Day 9: Disk Fragmenter ---")
{
    for (int i = 0; i < puzzleInput[0].length(); ++i)
        diskMap.push_back(puzzleInput[0][i] - '0');
    partitionDiskMap();
    expandDiskMap();
}


void Day9Solution::partitionDiskMap()
{
    size_t fileId {0};
    size_t expandedLocation {0};
    for (size_t compressedLocation = 0; compressedLocation < diskMap.size(); ++compressedLocation)
    {
        if (blockIsFile(compressedLocation))
        {
            files.push(Block{expandedLocation, diskMap[compressedLocation], fileId++});
        }
        else
            freeSpaces.push_back(Block{expandedLocation, diskMap[compressedLocation]});

        expandedLocation += diskMap[compressedLocation];
    }
}


bool Day9Solution::blockIsFile(size_t loc)
{
    return loc % 2 == 0;
}


void Day9Solution::expandDiskMap()
{
    size_t diskSize {0};
    for (const size_t &block : diskMap)
        diskSize += block;
    expandedDiskMap = vector<int>(diskSize);

    size_t diskBlock {0};
    int fileId {0};
    for (size_t i = 0; i < diskMap.size(); ++i)
    {
        for (size_t fileSize = 0; fileSize < diskMap[i]; ++fileSize)
        {
            if (i % 2 == 0)     //  Even
                expandedDiskMap[diskBlock] = fileId;

            else    //  Odd
                expandedDiskMap[diskBlock] = -1;    // -1 = empty space

            ++diskBlock;
        }

        if (i % 2 == 0)
            ++fileId;
    }
}


void Day9Solution::printExpandedDiskMap() const
{
    std::cout << std::endl;
    for (const int &individualBlock : expandedDiskMap)
        if (individualBlock >= 0)
            std::cout << individualBlock % 10;
        else
            std::cout << '.';
    std::cout << std::endl;
}


string Day9Solution::oneStarSolution()
{
    fragmentedCompaction();

    long long checksum {0};
    for (int index = 0; expandedDiskMap[index] != -1; ++index)
        checksum += index * expandedDiskMap[index];

    return std::to_string(checksum);
}


void Day9Solution::fragmentedCompaction()
{
    auto frontIterator = expandedDiskMap.begin();
    auto backIterator = expandedDiskMap.end()-1;

    while (frontIterator != backIterator)
    {
        while (*frontIterator != -1)
            ++frontIterator;

            //  If the array is even, incrementing one when decrementing the other will cause the iterators
            //  to never point to the same memory
        if (frontIterator == backIterator)
            break;

        while (*backIterator == -1)
            --backIterator;
        // front iterator is now pointing to an empty space while back iterator is pointing to a fileId

        *frontIterator = *backIterator;
        *backIterator = -1;
    }

}



string Day9Solution::twoStarSolution()
{
    expandDiskMap();    //  Reset expandedDiskMap to initial state
    contiguousCompaction();

    long long checksum {0};
    for (int individualBlock = 0; individualBlock < expandedDiskMap.size(); ++individualBlock)
    {
        if (expandedDiskMap[individualBlock] != -1)
            checksum += individualBlock * expandedDiskMap[individualBlock];
    }
    return std::to_string(checksum);
}


void Day9Solution::contiguousCompaction()
{
    while (!files.empty())
    {
        Block file = files.top();   //  Get value
        files.pop();                //  Remove value from top of stack

            // Find the first free space to the left of the file that can accommodate the file.
        auto freeSpace = freeSpaces.begin();
        while (freeSpace->size < file.size && freeSpace != freeSpaces.end())
            ++freeSpace;

            // If there's no space large enough for the file, leave it where it is.
        if (freeSpace == freeSpaces.end() || freeSpace->expandedLoc > file.expandedLoc)
            continue;

            // Move the file to the new location, free its old location, and remove the size from the free space.
        for (size_t offset = 0; offset < file.size; ++offset)
        {
            expandedDiskMap[freeSpace->expandedLoc + offset] = static_cast<int>(file.fileId);
            expandedDiskMap[file.expandedLoc + offset] = -1;
        }

            // Update freeSpace
        freeSpace->size -= file.size;
        freeSpace->expandedLoc += file.size;
    }
}
