#pragma once
#include <vector>
#include <unordered_map>
#include <list>
#include <ctime>
#include <iostream>

class MemoryManager {
private:
    struct Page {
        int pageNumber;
        bool present;     // Is page in physical memory?
        int frameNumber;  // Physical frame number if present
        time_t lastAccessed;
    };

    struct Frame {
        int frameNumber;
        int pageNumber;   // Page currently stored in frame
        bool occupied;
    };

    static const int PAGE_SIZE = 4096;  // 4KB pages
    static const int TOTAL_FRAMES = 128; // 512KB total physical memory
    
    std::unordered_map<int, Page> pageTable;
    std::vector<Frame> frames;
    std::list<int> lruList;  // For LRU page replacement
    int freeFrames;

public:
    MemoryManager() : freeFrames(TOTAL_FRAMES) {
        // Initialize frames
        frames.resize(TOTAL_FRAMES);
        for (int i = 0; i < TOTAL_FRAMES; i++) {
            frames[i] = {i, -1, false};
        }
    }

    // Allocate memory (returns virtual address)
    int allocateMemory(int size) {
        int numPages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
        int startPage = pageTable.size();

        for (int i = 0; i < numPages; i++) {
            pageTable[startPage + i] = {startPage + i, false, -1, time(nullptr)};
        }

        return startPage * PAGE_SIZE;
    }

    // Access memory at virtual address
    bool accessMemory(int virtualAddress) {
        int pageNumber = virtualAddress / PAGE_SIZE;
        int offset = virtualAddress % PAGE_SIZE;

        if (pageTable.find(pageNumber) == pageTable.end()) {
            std::cout << "Segmentation fault: invalid virtual address\n";
            return false;
        }

        return handlePageFault(pageNumber);
    }

    // Handle page fault
    bool handlePageFault(int pageNumber) {
        Page& page = pageTable[pageNumber];
        
        if (page.present) {
            // Page is already in memory, update LRU
            updateLRU(pageNumber);
            return true;
        }

        // Need to load page into memory
        if (freeFrames > 0) {
            // Find a free frame
            for (int i = 0; i < TOTAL_FRAMES; i++) {
                if (!frames[i].occupied) {
                    loadPage(pageNumber, i);
                    return true;
                }
            }
        } else {
            // Need to replace a page using LRU
            int victimPage = lruList.back();
            int frameNumber = pageTable[victimPage].frameNumber;
            
            // Evict the victim page
            pageTable[victimPage].present = false;
            pageTable[victimPage].frameNumber = -1;
            lruList.pop_back();

            // Load the new page
            loadPage(pageNumber, frameNumber);
            return true;
        }

        return false;
    }

private:
    void loadPage(int pageNumber, int frameNumber) {
        Page& page = pageTable[pageNumber];
        page.present = true;
        page.frameNumber = frameNumber;
        page.lastAccessed = time(nullptr);

        frames[frameNumber].occupied = true;
        frames[frameNumber].pageNumber = pageNumber;

        updateLRU(pageNumber);
        freeFrames--;
    }

    void updateLRU(int pageNumber) {
        // Remove if already in LRU list
        lruList.remove(pageNumber);
        // Add to front (most recently used)
        lruList.push_front(pageNumber);
    }

public:
    // Get memory stats
    void printMemoryStats() {
        int usedFrames = TOTAL_FRAMES - freeFrames;
        std::cout << "Memory Statistics:\n";
        std::cout << "Total Frames: " << TOTAL_FRAMES << "\n";
        std::cout << "Used Frames: " << usedFrames << "\n";
        std::cout << "Free Frames: " << freeFrames << "\n";
        std::cout << "Total Pages: " << pageTable.size() << "\n";
        std::cout << "Memory Usage: " << (usedFrames * 100.0 / TOTAL_FRAMES) << "%\n";
    }

    // Free allocated memory
    void freeMemory(int virtualAddress) {
        int pageNumber = virtualAddress / PAGE_SIZE;
        
        auto it = pageTable.find(pageNumber);
        if (it != pageTable.end()) {
            if (it->second.present) {
                frames[it->second.frameNumber].occupied = false;
                freeFrames++;
                lruList.remove(pageNumber);
            }
            pageTable.erase(it);
        }
    }
};