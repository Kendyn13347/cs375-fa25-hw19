class Process {
public:
    int pid;
    int priority;
    int cpuBurstRemaining;

    // (thread_id, address)
    std::vector<std::pair<int, unsigned int>> memoryAccesses;

    size_t accessIndex;

    // Thread ID → priority
    std::map<int, int> threadPriorities;

    Process(int pid, int priority);

    bool hasMoreAccesses() const;

    // Returns (thread_id, address)
    std::pair<int, unsigned int> nextAccess();

    void tick(int threadId);

    void addThread(int threadId, int threadPriority);
};
