#pragma once

#include <string>
#include "../userManager/UserManager.h"
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/FileSystemFuncs.h"
#include "CommandTrie.h"

#include "../fileSystem/file.h"
using namespace std;
#include <vector>

class CommandProcessor {
public:
    FileSystem *fileSystem;
    FileSystem *currentDir;
     CommandTrie commandTrie;

public:
    CommandProcessor(){
        // Initialize the user manager and file system
        fileSystem = new  FileSystem();
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