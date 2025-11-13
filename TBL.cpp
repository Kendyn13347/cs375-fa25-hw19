class TLBEntry {
public:
    int pid;
    int pageNumber;
    int frameNumber;
    int lastUsed;
};

class TLB {
private:
    std::vector<TLBEntry> tlbEntries;
    int currentTime;
    int maxSize;

public:
    TLB(int size);
    bool lookup(int pid, int pageNumber, int& frameNumber);
    void insert(int pid, int pageNumber, int frameNumber);
    void printStats() const;
};
