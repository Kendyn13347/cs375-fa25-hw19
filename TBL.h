#ifndef TLB_H
#define TLB_H

#include <vector>
#include <iostream>

// Represents a single entry in the TLB
class TLBEntry {
public:
    int pid;         // Process ID
    int pageNumber;  // Virtual page number
    int frameNumber; // Physical frame number
    int lastUsed;    // Timestamp for LRU replacement
};

// TLB with configurable size and LRU eviction
class TLB {
private:
    std::vector<TLBEntry> tlbEntries;
    int currentTime;
    int maxSize;

    // Stats (optional — add if you need them later)
    int tlbHits = 0;
    int tlbMisses = 0;

public:
    // Initialize TLB with a maximum size
    TLB(int size);

    // Lookup: returns true on TLB hit, false on miss
    // If hit: frameNumber is set to the matching frame
    bool lookup(int pid, int pageNumber, int& frameNumber);

    // Insert a new mapping, evicting LRU if full
    void insert(int pid, int pageNumber, int frameNumber);

    // Print stats: hits, misses, hit rate, etc.
    void printStats() const;
};

#endif
