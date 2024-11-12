#pragma once
#include "./FileSystem.h"

#include "../linkedList/LinkedList.h"
#include <iostream>
using namespace std;
FileSystem* FileSystem::changeDirectory(string& dirName) {

    if (dirName == "..") {
        if (parent != nullptr) {
            cout << "Moved up to parent directory: " << parent->getName() << "\n";
            return parent;
        } else {
            cout << "Already at the root directory.\n";
            return this; 
        }
    } else {
        FileSystem* newDir = findDirectory(dirName);
        if (newDir) {
            cout << "Changed directory to: " << newDir->getName() << "\n";
            return newDir;
        } else {
            cout << "No such directory exists: " << dirName << "\n";
            return this; 
        }
    }
}
