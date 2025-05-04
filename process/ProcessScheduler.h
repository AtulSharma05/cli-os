#ifndef PROCESS_SCHEDULER_H
#define PROCESS_SCHEDULER_H

#include "Process.h"
#include <queue>
#include <iostream>

class ProcessScheduler {
private:
    std::queue<Process> processQueue; // Queue to manage processes
    int timeQuantum;                 // Time slice for Round Robin

public:
    ProcessScheduler(int quantum) : timeQuantum(quantum) {}

    void addProcess(const Process& process) {
        processQueue.push(process);
        std::cout << "Process " << process.pid << " added to the queue.\n";
    }

    void executeProcesses() {
        std::cout << "Starting Round Robin Scheduling...\n";
        while (!processQueue.empty()) {
            Process current = processQueue.front();
            processQueue.pop();

            std::cout << "Executing Process " << current.pid << "...\n";

            if (current.remainingTime > timeQuantum) {
                current.remainingTime -= timeQuantum;
                std::cout << "Process " << current.pid << " executed for " << timeQuantum << " units. Remaining time: " << current.remainingTime << "\n";
                processQueue.push(current); // Re-add process to the queue
            } else {
                std::cout << "Process " << current.pid << " completed execution.\n";
            }
        }
        std::cout << "All processes have been executed.\n";
    }
};

#endif