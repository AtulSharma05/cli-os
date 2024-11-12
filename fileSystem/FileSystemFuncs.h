#pragma once
#include "FileSystem.h"
#include <iostream>
using namespace std;



void FileSystem::listFiles() {
        cout << "Contents of " << name << ":" << endl;

        
        if (!children.isEmpty()) {
            cout << "Directories:" << endl;
            children.display(); 
        } else {
            cout << "No directories." << endl;
        }

        // List files
        if (!files.isEmpty()) {
            cout << "Files:" << endl;
            files.display(); // Display names of files
        } else {
            cout << "No files." << endl;
        }
    }



void FileSystem::printWorkingDirectory() {
    if (parent != nullptr) {
       parent->printWorkingDirectory(); // Recursive call to print the full path
       
    }
    cout << "/" << this->name; // Print current directory name

}
