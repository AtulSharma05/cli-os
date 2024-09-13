#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <vector>
#include <map>
#include "Stack.h"

class CommandProcessor {
public:
    void redoCommand();
    void undoCommand();
    void executeCommand(const std::string& command);
    void showHistory() const;
    void createFile(const std::string& filename);
    void deleteFile(const std::string& filename);
    void listFiles() const; // Existing method
    void changeDirectory(const std::string& directory);
    void displayCurrentDirectory() const;

private:
    std::vector<std::string> history;
    Stack<std::string> undoHistory;
    std::string currentDirectory;
    std::map<std::string, std::string> files; // For simplicity, filename -> content mapping

    void addHistory(const std::string& command);
    void listFilesInDirectory() const; // Add this method
};

#endif // COMMANDPROCESSOR_H
