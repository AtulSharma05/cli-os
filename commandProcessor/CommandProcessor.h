#pragma once

#include <string>
#include "../userManager/UserManager.h"
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/FileSystemFuncs.h"

#include "../fileSystem/file.h"
using namespace std;
#include <vector>

class CommandProcessor {
private:
    FileSystem *fileSystem;
    FileSystem *currentDir;

public:
    CommandProcessor(){
        // Initialize the user manager and file system
        fileSystem = new  FileSystem();
        currentDir = fileSystem;

    };
    ~CommandProcessor() {
    delete fileSystem;
}

    void processCommand(vector<UserManager>&,string& );
    void printCurrDir(){
        cout<<currentDir->getName();
    };
};

