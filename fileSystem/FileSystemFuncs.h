#pragma once
#include "FileSystem.h"
#include <iostream>
using namespace std;



void FileSystem::listFiles() {
        std::cout << "Contents of " << name << ":" << std::endl;

        // List directories
        if (!children.isEmpty()) {
            std::cout << "Directories:" << std::endl;
            children.display(); // Display names of directories
        } else {
            std::cout << "No directories." << std::endl;
        }

        // List files
        if (!files.isEmpty()) {
            std::cout << "Files:" << std::endl;
            files.display(); // Display names of files
        } else {
            std::cout << "No files." << std::endl;
        }
    }


void FileSystem::changeDirectory(string& dirName) {

}

void FileSystem::printWorkingDirectory() {

}
