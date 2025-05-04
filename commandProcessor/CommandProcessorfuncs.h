#pragma once
#include "CommandProcessor.h"
#include "../userManager/UserManager.h" 
#include "../userManager/UserManagerfunc.h" 
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/makeDirectory.h"
#include "../fileSystem/makeFile.h"
#include "../fileSystem/file.h"
#include "../fileSystem/findDirectory.h"
#include "../fileSystem/changeDirectory.h"
#include "../fileSystem/findDirectoryPath.h"
#include "../fileSystem/findCommand.h"
#include "../fileSystem/compress.h/map.h"
#include "../fileSystem/findFile.h"
#include "../fileSystem/nano.h"
#include "../process/ProcessScheduler.h" 


#include <iostream>
#include <vector>

ProcessScheduler scheduler(5);
int processCounter = 1;
void CommandProcessor::processCommand(vector<UserManager>&users, string& command) {
    if(command.substr(0,5)=="find "){
    size_t pathStart = 5;
    size_t typePos = command.find(' ', pathStart);
    size_t namePos = command.find(' ', typePos + 1);
        string path = command.substr(pathStart, typePos - pathStart);
        string type = command.substr(typePos + 1, namePos - typePos - 1);
        string name = command.substr(namePos+1);

        // Validate the type
        if (type != "f" && type != "d") {
            cout << "Invalid type. Use 'f' for file or 'd' for directory." << endl;
            return;
        }

        // Use findCommand on the current directory
        currentDir->findCommand(path, type, name);
        
    }else 
    if (command == "ls") {
        currentDir->listFiles();

    } else if (command.substr(0, 6) == "mkdir ") {

        string dirName = command.substr(6);
        currentDir->makeDirectory(dirName);

    }else if (command.substr(0, 7) == "mkfile ") {

        string filName = command.substr(7);
        currentDir->makeFile(filName);

    } 
    else if (command.substr(0, 2) == "cd") {
        clearLines();
        if(command=="cd"){
            while(currentDir->parent!=nullptr){
                currentDir = currentDir->parent;
            }
        }else{


        string dirName = command.substr(3); 
        
      currentDir=currentDir->changeDirectory(dirName);}
    } else if (command == "pwd") {
        currentDir->printWorkingDirectory();
    } else if (command.substr(0, 8) == "adduser ") {
        string userInfo = command.substr(8);
        int spacePos = userInfo.find(' ');
        string username = userInfo.substr(0, spacePos);
        string password = userInfo.substr(spacePos + 1);
        UserManager newuser(username,password);
        users.push_back(newuser);
    } else if (command.substr(0, 4) == "zip ") {
        string filename = command.substr(4);
        currentDir->zip(filename);
    } else if (command.substr(0, 6) == "unzip ") {
        string filename = command.substr(6);
        currentDir->unzip(filename);
    } else if(command.substr(0,5)=="nano "){
        string filename = command.substr(5);
        currentDir->nanoEditor(filename);
    }
    else if (command.substr(0, 6) == "login ") {
        string userInfo = command.substr(6);
        int spacePos = userInfo.find(' ');
        string username = userInfo.substr(0, spacePos);
        string password = userInfo.substr(spacePos + 1);
        if (authenticateUser(users,username, password)) {
            cout << "Login successful.\n";
        } else {
            cout << "Login failed.\n";
        }
    } else if(command.substr(0,5)=="finds"){
        string name = command.substr(5 + 1);
        file* temp=currentDir->findFile(name);
        if(temp!=nullptr){
        cout<<temp->name;
        }else{ cout<<"No such file exits";
        }

    } else if (command.substr(0, 3) == "rm ") {
        string target = command.substr(3);
        if (currentDir->findFile(target)) {
            currentDir->removeFile(target);
            cout << "Removed file: " << target << "\n";
        } else if (currentDir->findDirectory(target)) {
            currentDir->removeNode(currentDir, target);
            cout << "Removed directory: " << target << "\n";
        } else {
            cout << "No such file or directory: " << target << "\n";
        }
    } else if (command.substr(0, 3) == "mv ") {
        size_t spacePos = command.find(' ', 3);
        string source = command.substr(3, spacePos - 3);
        string targetDirName = command.substr(spacePos + 1);
        FileSystem* targetDir = currentDir->findDirectory(targetDirName);
        if (currentDir->findFile(source)) {
            if (targetDir != nullptr) {
                currentDir->moveFile(source, targetDir);
                cout << "Moved file: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else if (currentDir->findDirectory(source)) {
            if (targetDir != nullptr) {
                currentDir->moveNode(currentDir, targetDir, source);
                cout << "Moved directory: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else {
            cout << "No such file or directory: " << source << "\n";
        }
    } else if (command.substr(0, 3) == "cp ") {
        size_t spacePos = command.find(' ', 3);
        string source = command.substr(3, spacePos - 3);
        string targetDirName = command.substr(spacePos + 1);
        FileSystem* targetDir = currentDir->findDirectory(targetDirName);
        if (currentDir->findFile(source)) {
            if (targetDir != nullptr) {
                currentDir->copyFile(source, targetDir);
                cout << "Copied file: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else if (currentDir->findDirectory(source)) {
            if (targetDir != nullptr) {
                currentDir->copyNode(currentDir, targetDir, source);
                cout << "Copied directory: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else {
            cout << "No such file or directory: " << source << "\n";
        }
    }
    // New resource management commands
    else if (command == "ps") {
        cout << "Available processes and their resources:\n";
        // Process list is handled internally by ResourceManager
    }
    else if (command == "newproc") {
        int pid = resourceManager.createProcess();
        cout << "Created new process with PID: " << pid << "\n";
    }
    else if (command.substr(0, 8) == "request ") {
        size_t spacePos1 = command.find(' ', 8);
        if (spacePos1 != string::npos) {
            int pid = stoi(command.substr(8, spacePos1 - 8));
            string resource = command.substr(spacePos1 + 1);
            bool granted = resourceManager.requestResource(pid, resource);
            if (granted) {
                cout << "Resource '" << resource << "' allocated to process " << pid << "\n";
            } else {
                cout << "Resource '" << resource << "' is busy. Process " << pid << " added to wait queue.\n";
            }
        }
    }
    else if (command.substr(0, 8) == "release ") {
        size_t spacePos1 = command.find(' ', 8);
        if (spacePos1 != string::npos) {
            int pid = stoi(command.substr(8, spacePos1 - 8));
            string resource = command.substr(spacePos1 + 1);
            resourceManager.releaseResource(pid, resource);
            cout << "Resource '" << resource << "' released by process " << pid << "\n";
        }
    }
    else if (command == "checkdl") {
        vector<int> deadlocked = resourceManager.detectDeadlocks();
        if (deadlocked.empty()) {
            cout << "No deadlocks detected.\n";
        } else {
            cout << "Deadlock detected! Involved processes: ";
            for (int pid : deadlocked) {
                cout << pid << " ";
            }
            cout << "\n";
        }
    }
    // Disk scheduling commands
    else if (command.substr(0, 9) == "diskseek ") {
        try {
            int position = stoi(command.substr(9));
            diskScheduler.setCurrentPosition(position);
            cout << "Current disk position set to: " << position << "\n";
        } catch (const std::exception& e) {
            cout << "Invalid position. Please enter a valid number.\n";
        }
    }
    else if (command.substr(0, 8) == "diskreq ") {
        try {
            int cylinder = stoi(command.substr(8));
            diskScheduler.addRequest(cylinder);
            cout << "Added disk request for cylinder: " << cylinder << "\n";
        } catch (const std::exception& e) {
            cout << "Invalid cylinder number. Please enter a valid number.\n";
        }
    }
    else if (command == "diskfcfs") {
        auto [sequence, seekTime] = diskScheduler.fcfs();
        cout << "FCFS Disk Scheduling Result:\n";
        cout << "Sequence: ";
        for (int pos : sequence) cout << pos << " ";
        cout << "\nTotal seek time: " << seekTime << "\n";
    }
    else if (command == "diskscan") {
        auto [sequence, seekTime] = diskScheduler.scan();
        cout << "SCAN (Elevator) Disk Scheduling Result:\n";
        cout << "Sequence: ";
        for (int pos : sequence) cout << pos << " ";
        cout << "\nTotal seek time: " << seekTime << "\n";
    }
    else if (command == "diskcscan") {
        auto [sequence, seekTime] = diskScheduler.cscan();
        cout << "C-SCAN Disk Scheduling Result:\n";
        cout << "Sequence: ";
        for (int pos : sequence) cout << pos << " ";
        cout << "\nTotal seek time: " << seekTime << "\n";
    }
    else if (command == "diskclear") {
        diskScheduler.clearRequests();
        cout << "Cleared all disk requests.\n";
    }
    else if (command == "addprocess") {
        // Add a new process to the scheduler
        int burstTime;
        cout << "Enter burst time for the process: ";
        cin >> burstTime;
        cin.ignore(); // Clear newline from input buffer

        Process newProcess(processCounter++, burstTime);
        scheduler.addProcess(newProcess);

    } else if (command == "runprocesses") {
        // Execute all processes using Round Robin scheduling
        scheduler.executeProcesses();

    } 
    // Memory management commands
    else if (command.substr(0, 9) == "memalloc ") {
        try {
            int size = stoi(command.substr(9));
            int virtualAddress = memoryManager.allocateMemory(size);
            cout << "Memory allocated at virtual address: 0x" << hex << virtualAddress << dec << "\n";
        } catch (const std::exception& e) {
            cout << "Invalid size. Please enter a valid number.\n";
        }
    }
    else if (command.substr(0, 10) == "memaccess ") {
        try {
            int virtualAddress = stoi(command.substr(10));
            bool success = memoryManager.accessMemory(virtualAddress);
            if (success) {
                cout << "Memory access successful at virtual address: 0x" << hex << virtualAddress << dec << "\n";
            }
        } catch (const std::exception& e) {
            cout << "Invalid address. Please enter a valid number.\n";
        }
    }
    else if (command.substr(0, 8) == "memfree ") {
        try {
            int virtualAddress = stoi(command.substr(8));
            memoryManager.freeMemory(virtualAddress);
            cout << "Memory freed at virtual address: 0x" << hex << virtualAddress << dec << "\n";
        } catch (const std::exception& e) {
            cout << "Invalid address. Please enter a valid number.\n";
        }
    }
    else if (command == "memstats") {
        memoryManager.printMemoryStats();
    }
    else {
        cout << "Unknown command.\n";
    }
}
