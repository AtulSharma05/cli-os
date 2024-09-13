#include "CommandProcessor.h"
#include <iostream>

void CommandProcessor::redoCommand() {
    if (!undoHistory.isEmpty()) {
        std::string command = undoHistory.top();
        undoHistory.pop();
        executeCommand(command); // Re-execute the command
    }
}

void CommandProcessor::undoCommand() {
    if (!history.isEmpty()) {
        std::string command = history.top();
        history.pop();
        undoHistory.push(command); // Store command for redo
        // Implement actual undo logic if needed
    }
}

void CommandProcessor::executeCommand(const std::string& command) {
    addHistory(command);
    if (command.substr(0, 6) == "create") {
        createFile(command.substr(7));
    } else if (command.substr(0, 6) == "delete") {
        deleteFile(command.substr(7));
    } else if (command == "list") {
        listFilesInDirectory(); // Change this line to call listFilesInDirectory()
    } else if (command.substr(0, 3) == "cd ") {
        changeDirectory(command.substr(3));
    } else if (command == "pwd") {
        displayCurrentDirectory();
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

void CommandProcessor::showHistory() const {
    while(!history.isEmpty()) {
        std::cout << history.top()<< std::endl;
    }
}

void CommandProcessor::createFile(const std::string& filename) {
    files[filename] = ""; // Create an empty file
    std::cout << "File created: " << filename << std::endl;
}

void CommandProcessor::deleteFile(const std::string& filename) {
    files.erase(filename);
    std::cout << "File deleted: " << filename << std::endl;
}

void CommandProcessor::listFilesInDirectory() const {
    std::cout << "Files in current directory:" << std::endl;
    for (const auto& file : files) {
        std::cout << file.first << std::endl;
    }
}

void CommandProcessor::changeDirectory(const std::string& directory) {
    currentDirectory = directory;
    std::cout << "Changed directory to: " << directory << std::endl;
}

void CommandProcessor::displayCurrentDirectory() const {
    std::cout << "Current directory: " << currentDirectory << std::endl;
}

void CommandProcessor::addHistory(const std::string& command) {
    history.push(command);
}
