#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
    int pid;               // Process ID
    int burstTime;         // Total time required by the process
    int remainingTime;     // Remaining time for execution

    Process(int id, int burst) : pid(id), burstTime(burst), remainingTime(burst) {}
};

#endif