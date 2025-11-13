class CPU {
private:
    int cyclesExecuted;
    int contextSwitches;
    int threadSwitches;

public:
    void execute(Process& p, int threadId);
    void printStats() const;
};
