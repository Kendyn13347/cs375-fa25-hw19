#include <iostream>
#include <vector>
#include "Process.h"
#include "CPU.h"

// Simple helper: returns true if ANY process still has memory accesses left
bool anyProcessHasWork(const std::vector<Process> &procs) {
    for (const auto &p : procs) {
        if (p.hasMoreAccesses()) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    // ---------------------------------------------------------
    // 1. Basic configuration (you can extend this with flags)
    // ---------------------------------------------------------
    std::string schedulingPolicy = "RoundRobin";   // later: "MLFQ", "FCFS", "Priority"
    int tlbSize = 16;                              // later: read from args / config file

    std::cout << "=== Demand Paging & CPU Scheduling Simulator ===\n";
    std::cout << "Scheduling policy: " << schedulingPolicy << "\n";
    std::cout << "TLB size: " << tlbSize << " entries\n\n";

    // ---------------------------------------------------------
    // 2. Create some example processes and memory access traces
    //    (In the real lab, you'll probably read this from a file)
    // ---------------------------------------------------------
    std::vector<Process> processes;

    // Process 1: mostly sequential accesses (e.g., scanning an array)
    Process p1(1, /*priority*/ 1);
    p1.cpuBurstRemaining = 20;
    p1.addThread(0, /*threadPriority*/ 1);

    for (unsigned int addr = 0x1000; addr < 0x1000 + 10 * 0x10; addr += 0x10) {
        p1.memoryAccesses.push_back({0, addr}); // thread 0
    }

    // Process 2: more random / “scattered” accesses
    Process p2(2, /*priority*/ 2);
    p2.cpuBurstRemaining = 25;
    p2.addThread(0, 2);

    unsigned int randomAddrs[] = {0x2000, 0x2FF0, 0x2100, 0x2A00, 0x2B10,
                                  0x2400, 0x2FE0, 0x2200, 0x2C20, 0x2300};
    for (unsigned int addr : randomAddrs) {
        p2.memoryAccesses.push_back({0, addr});
    }

    // Process 3: localized “hot spot” accesses (e.g., working set behavior)
    Process p3(3, /*priority*/ 0);  // higher priority (lower number)
    p3.cpuBurstRemaining = 15;
    p3.addThread(0, 0);

    for (int i = 0; i < 10; ++i) {
        unsigned int addr = 0x3000 + (i % 3) * 0x10;  // repeatedly hit 3 pages
        p3.memoryAccesses.push_back({0, addr});
    }

    processes.push_back(p1);
    processes.push_back(p2);
    processes.push_back(p3);

    // ---------------------------------------------------------
    // 3. Create the CPU (and later, your paging / TLB components)
    // ---------------------------------------------------------
    CPU cpu;

    // In a more complete design you might have something like:
    // MemorySystem mem(tlbSize, /*other params*/);
    // Scheduler scheduler(schedulingPolicy);
    //
    // For now, we’ll just do a simple round-robin over processes.

    // ---------------------------------------------------------
    // 4. Main simulation loop
    //    - Pick a process
    //    - Pick a thread (we only used thread 0 here)
    //    - Ask the CPU to execute one step for that (process, thread)
    // ---------------------------------------------------------
    size_t currentIndex = 0;

    while (anyProcessHasWork(processes)) {
        Process &current = processes[currentIndex];

        if (current.hasMoreAccesses()) {
            int threadId = 0; // only one thread for now
            cpu.execute(current, threadId);
        }

        // Move to next process (basic Round Robin)
        currentIndex = (currentIndex + 1) % processes.size();
    }

    // ---------------------------------------------------------
    // 5. Print statistics (cycles, context switches, etc.)
    //    Later you’ll also print:
    //      - TLB hits/misses
    //      - Page faults
    //      - Per-process stats and timelines
    // ---------------------------------------------------------
    std::cout << "\n=== Simulation finished ===\n";
    cpu.printStats();

    return 0;
}
