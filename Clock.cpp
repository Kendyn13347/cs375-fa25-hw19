struct FrameEntry {
    int pid;
    int pageNumber;
    bool referenced;
    bool modified; // Tracks if page was modified
};

class Clock {
private:
    std::vector<FrameEntry> frames;
    size_t clockHand;

public:
    Clock(int frameCount);
    int evictAndReplace(int pid, int pageNum, int& evictedPage, bool isModified);
};
