#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include "FileSystem.h"

class ResourceManager {
private:
    struct Process {
        int pid;
        std::set<std::string> allocated;   // Resources allocated to this process
        std::set<std::string> requested;   // Resources requested by this process
    };

    std::map<int, Process> processes;
    std::map<std::string, int> resources;  // Resource name to owner process ID
    int nextPid;

public:
    ResourceManager() : nextPid(1) {}

    int createProcess() {
        processes[nextPid] = Process{nextPid};
        return nextPid++;
    }

    bool requestResource(int pid, const std::string& resource) {
        if (resources.find(resource) != resources.end()) {
            processes[pid].requested.insert(resource);
            return false;  // Resource is busy
        }
        
        resources[resource] = pid;
        processes[pid].allocated.insert(resource);
        return true;
    }

    void releaseResource(int pid, const std::string& resource) {
        if (resources[resource] == pid) {
            resources.erase(resource);
            processes[pid].allocated.erase(resource);
        }
    }

    // Deadlock detection algorithm
    std::vector<int> detectDeadlocks() {
        std::vector<int> deadlockedProcesses;
        std::map<int, std::set<int>> waitForGraph;
        
        // Build the wait-for graph
        for (const auto& [pid, process] : processes) {
            for (const auto& requestedResource : process.requested) {
                if (resources.find(requestedResource) != resources.end()) {
                    int ownerPid = resources[requestedResource];
                    if (ownerPid != pid) {
                        waitForGraph[pid].insert(ownerPid);
                    }
                }
            }
        }

        // Detect cycles using DFS
        std::set<int> visited;
        std::set<int> recursionStack;

        for (const auto& [pid, _] : processes) {
            if (detectCycle(pid, waitForGraph, visited, recursionStack)) {
                deadlockedProcesses.push_back(pid);
            }
        }

        return deadlockedProcesses;
    }

private:
    bool detectCycle(int pid, const std::map<int, std::set<int>>& waitForGraph, 
                    std::set<int>& visited, std::set<int>& recursionStack) {
        if (recursionStack.find(pid) != recursionStack.end())
            return true;
        if (visited.find(pid) != visited.end())
            return false;

        visited.insert(pid);
        recursionStack.insert(pid);

        if (waitForGraph.find(pid) != waitForGraph.end()) {
            for (int neighbor : waitForGraph.at(pid)) {
                if (detectCycle(neighbor, waitForGraph, visited, recursionStack))
                    return true;
            }
        }

        recursionStack.erase(pid);
        return false;
    }
};