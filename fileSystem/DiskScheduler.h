#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>

class DiskScheduler {
private:
    int currentPosition;
    const int MAX_CYLINDER = 199;  // Maximum cylinder number
    std::vector<int> requestQueue;

public:
    DiskScheduler() : currentPosition(0) {}

    void setCurrentPosition(int pos) {
        currentPosition = pos;
    }

    void addRequest(int cylinderNo) {
        if (cylinderNo >= 0 && cylinderNo <= MAX_CYLINDER) {
            requestQueue.push_back(cylinderNo);
        }
    }

    // First Come First Serve (FCFS)
    std::pair<std::vector<int>, int> fcfs() {
        if (requestQueue.empty()) return {std::vector<int>(), 0};

        std::vector<int> sequence = requestQueue;
        int totalSeekTime = 0;
        int current = currentPosition;

        for (int next : sequence) {
            totalSeekTime += std::abs(next - current);
            current = next;
        }

        return {sequence, totalSeekTime};
    }

    // SCAN (Elevator) Algorithm
    std::pair<std::vector<int>, int> scan(bool direction = true) {
        if (requestQueue.empty()) return {std::vector<int>(), 0};

        std::vector<int> sequence;
        std::vector<int> requests = requestQueue;
        requests.push_back(currentPosition);
        std::sort(requests.begin(), requests.end());

        int current_pos = currentPosition;
        int total_seek_time = 0;
        
        auto start = std::lower_bound(requests.begin(), requests.end(), currentPosition);
        int start_index = start - requests.begin();

        if (direction) { // Moving towards higher cylinder numbers
            // First move towards higher numbers
            for (int i = start_index; i < requests.size(); i++) {
                sequence.push_back(requests[i]);
                total_seek_time += std::abs(requests[i] - current_pos);
                current_pos = requests[i];
            }
            // Then move towards lower numbers
            for (int i = start_index - 1; i >= 0; i--) {
                sequence.push_back(requests[i]);
                total_seek_time += std::abs(requests[i] - current_pos);
                current_pos = requests[i];
            }
        } else { // Moving towards lower cylinder numbers
            // First move towards lower numbers
            for (int i = start_index - 1; i >= 0; i--) {
                sequence.push_back(requests[i]);
                total_seek_time += std::abs(requests[i] - current_pos);
                current_pos = requests[i];
            }
            // Then move towards higher numbers
            for (int i = start_index; i < requests.size(); i++) {
                sequence.push_back(requests[i]);
                total_seek_time += std::abs(requests[i] - current_pos);
                current_pos = requests[i];
            }
        }

        return {sequence, total_seek_time};
    }

    // C-SCAN (Circular SCAN) Algorithm
    std::pair<std::vector<int>, int> cscan() {
        if (requestQueue.empty()) return {std::vector<int>(), 0};

        std::vector<int> sequence;
        std::vector<int> requests = requestQueue;
        requests.push_back(currentPosition);
        std::sort(requests.begin(), requests.end());

        int current_pos = currentPosition;
        int total_seek_time = 0;

        auto start = std::lower_bound(requests.begin(), requests.end(), currentPosition);
        int start_index = start - requests.begin();

        // Move towards higher cylinder numbers
        for (int i = start_index; i < requests.size(); i++) {
            sequence.push_back(requests[i]);
            total_seek_time += std::abs(requests[i] - current_pos);
            current_pos = requests[i];
        }

        // Jump to beginning (add seek time)
        if (!requests.empty()) {
            total_seek_time += MAX_CYLINDER - current_pos; // Go to end
            total_seek_time += MAX_CYLINDER; // Go to beginning
            current_pos = 0;
        }

        // Continue from beginning up to the start position
        for (int i = 0; i < start_index; i++) {
            sequence.push_back(requests[i]);
            total_seek_time += std::abs(requests[i] - current_pos);
            current_pos = requests[i];
        }

        return {sequence, total_seek_time};
    }

    void clearRequests() {
        requestQueue.clear();
    }
};