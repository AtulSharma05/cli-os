#pragma once

#include <string>
#include "../userManager/UserManager.h"
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/FileSystemFuncs.h"
#include "../fileSystem/ResourceManager.h"
#include "../fileSystem/DiskScheduler.h"
#include "../fileSystem/MemoryManager.h"
#include "CommandTrie.h"
#include "../fileSystem/file.h"
using namespace std;
#include <vector>

class CommandProcessor {
public:
    FileSystem *fileSystem;
    FileSystem *currentDir;
    CommandTrie commandTrie;
    ResourceManager resourceManager;
    DiskScheduler diskScheduler;
    MemoryManager memoryManager;  // Added MemoryManager

public:
    CommandProcessor(){
        fileSystem = new FileSystem();
        currentDir = fileSystem;
        initializeCommands();
    };
    ~CommandProcessor() {
        delete fileSystem;
    }

    void processCommand(vector<UserManager>&,string& );
    void printCurrDir(){
        cout<<currentDir->getName();
    };
    void initializeCommands();
    void suggestCommand(string& prefix);
};

void CommandProcessor::initializeCommands() {
    // Existing commands
    commandTrie.insertCommand("ls");
    commandTrie.insertCommand("find");
    commandTrie.insertCommand("mkdir");
    commandTrie.insertCommand("mkfile");
    commandTrie.insertCommand("cd");
    commandTrie.insertCommand("pwd");
    commandTrie.insertCommand("adduser");
    commandTrie.insertCommand("zip");
    commandTrie.insertCommand("unzip");
    commandTrie.insertCommand("nano");
    commandTrie.insertCommand("finds");
    commandTrie.insertCommand("rm");
    commandTrie.insertCommand("mv");
    commandTrie.insertCommand("cp");
    
    // New resource management commands
    commandTrie.insertCommand("ps");           // List processes
    commandTrie.insertCommand("newproc");      // Create new process
    commandTrie.insertCommand("request");      // Request a resource
    commandTrie.insertCommand("release");      // Release a resource
    commandTrie.insertCommand("checkdl");      // Check for deadlocks

    // New disk scheduling commands
    commandTrie.insertCommand("diskseek");    // Set current disk position
    commandTrie.insertCommand("diskreq");     // Add disk request
    commandTrie.insertCommand("diskfcfs");    // Run FCFS algorithm
    commandTrie.insertCommand("diskscan");    // Run SCAN algorithm
    commandTrie.insertCommand("diskcscan");   // Run C-SCAN algorithm
    commandTrie.insertCommand("diskclear");   // Clear disk requests

    // New memory management commands
    commandTrie.insertCommand("memalloc");   // Allocate memory
    commandTrie.insertCommand("memaccess");  // Access memory
    commandTrie.insertCommand("memfree");    // Free memory
    commandTrie.insertCommand("memstats");   // Show memory statistics
}

void CommandProcessor::suggestCommand(string& prefix) {
    vector<string> suggestions = commandTrie.getAutoCompleteSuggestions(prefix);

    if (!suggestions.empty()) {
       
        for (const auto& suggestion : suggestions) {
            cout << " - " << suggestion << '\n';
        }
    } else {
        
    }
}