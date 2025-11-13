#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <map>
#include <queue>
#include <vector>
#include "Process.h"

// Supported scheduling policies
enum class SchedulingPolicy { FCFS, RoundRobin, Priority, MLFQ };

class Scheduler {
private:
    SchedulingPolicy policy;

    // Map: PID → Process object
    std::map<int, Process> processes;

    // For MLFQ: multiple ready queues (one per priority level)
    std::vector<std::queue<int>> readyQueues;

    int quantum;  // Used for Round Robin (default = 4 in assignment)

public:
    // Constructor: choose scheduling policy and pass TLB size if needed
    Scheduler(SchedulingPolicy policy, int tlbSize);

    // Add a process only if it does not already exist in "processes"
    void addProcessIfNotExists(int pid);

    // Return reference to process in table
    Process& getProcess(int pid);

    // Core scheduler step: simulate CPU time, queues, context switches, etc.
    void tick();

    // MLFQ priority adjustment
    void adjustPriority(int pid, int threadId);
};

#endif
