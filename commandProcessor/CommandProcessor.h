#pragma once

#include <string>
#include "../userManager/UserManager.h"
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/FileSystemFuncs.h"
#include "../fileSystem/file.h"

#include <vector>

class CommandProcessor {
private:
    FileSystem *fileSystem;

public:
    CommandProcessor(){
        // Initialize the user manager and file system
        fileSystem = new  FileSystem();

    };
    void processCommand(vector<UserManager>&,string& );
};

