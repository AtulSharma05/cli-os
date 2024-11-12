#pragma once
#include "./FileSystem.h"
#include "../linkedList/LinkedList.h"
#include <iostream>
using namespace std;
#include <sstream>

FileSystem* FileSystem::findDirectoryPath(string& path) {
    // Determine starting point: absolute paths start from root
    FileSystem* current = this;
    if (path[0] == '/') { // absolute path
        while (current->parent != nullptr) {
            current = current->parent; // Move to root
        }
        path = path.substr(1); // Remove leading '/'
    }

    // Split the path by '/'
    stringstream ss(path);
    string dirName;

    while (getline(ss, dirName, '/')) {
        if (dirName == "..") {  // Move up to parent directory
            if (current->parent != nullptr) {
                current = current->parent;
            } else {
                cout << "Path error: already at the root directory.\n";
                return nullptr;
            }
        } else if (dirName != "." && !dirName.empty()) { // Move to the child directory
            current = current->findDirectory(dirName);
            if (current == nullptr) {
                cout << "Directory not found: " << dirName << endl;
                return nullptr;
            }
        }
    }
    return current;
}
