enum class SchedulingPolicy { FCFS, RoundRobin, Priority, MLFQ };

class Scheduler {
private:
    SchedulingPolicy policy;
    std::map<int, Process> processes;
    std::vector<std::queue<int>> readyQueues; // For MLFQ: multiple priority queues
    int quantum;

public:
    Scheduler(SchedulingPolicy policy, int tlbSize);
    void addProcessIfNotExists(int pid);
    Process& getProcess(int pid);
    void tick(); // Advance time, simulate scheduling and thread execution
    void adjustPriority(int pid, int threadId); // For MLFQ
};
