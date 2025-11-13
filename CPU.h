#ifndef CPU_H
#define CPU_H

#include "Process.h"

class CPU {
private:
    int cyclesExecuted;
    int contextSwitches;
    int threadSwitches;

public:
    CPU();

    // Simulate executing a process on a specific thread
    void execute(Process& p, int threadId);

    // Print CPU stats (cycles, context switches, etc.)
    void printStats() const;
};

#endif
