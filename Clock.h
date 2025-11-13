#ifndef CLOCK_H
#define CLOCK_H

#include <vector>
#include <cstddef>

// One frame in physical memory for the Clock replacement algorithm
struct FrameEntry {
    int pid;          // Process ID owning this page
    int pageNumber;   // Virtual page number
    bool referenced;  // Reference bit (R)
    bool modified;    // Modified bit (M) - used for write-back decisions
};

// Advanced Clock replacement algorithm (Clock with referenced + modified bits)
class Clock {
private:
    std::vector<FrameEntry> frames; // All physical frames
    size_t clockHand;               // Current sweep hand position

public:
    // Initialize Clock with a fixed number of physical frames
    Clock(int frameCount);

    // Perform eviction and replacement:
    //   - pid/pageNum = incoming page
    //   - evictedPage = outgoing page number (set by function)
    //   - isModified  = whether replacement page will be marked modified
    //
    // Returns the frame index where the new page was placed.
    int evictAndReplace(int pid, int pageNum, int& evictedPage, bool isModified);
};

#endif
