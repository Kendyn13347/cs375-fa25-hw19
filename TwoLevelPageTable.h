#ifndef TWOLEVELPAGETABLE_H
#define TWOLEVELPAGETABLE_H

#include <map>
#include <set>
#include <utility>
#include <iostream>

// Two-level page table for virtual → physical translation.
// Outer index = directory (first level)
// Inner index = page table entry (second level)

class TwoLevelPageTable {
private:
    // First level: maps (pid, outer_page) → second-level table ID
    std::map<std::pair<int, int>, int> firstLevel;

    // Second level: maps (pid, inner_page) → physical frame number
    std::map<std::pair<int, int>, int> secondLevel;

    // Tracks which (pid, page#) are currently in memory
    std::set<std::pair<int, int>> memoryPages;

    int pageCount; // total number of physical frames OR per-process limit

public:
    // Constructor
    TwoLevelPageTable(int pageCount);

    // Check if a page is in memory
    bool isInMemory(int pid, int pageNum) const;

    // Return the physical frame if page is present; caller must ensure presence
    int getFrame(int pid, int pageNum) const;

    // Load a page into memory and update both levels
    void loadPage(int pid, int pageNum, int frameNum);

    // Print statistics for debugging (optional)
    void printStats() const;
};

#endif
