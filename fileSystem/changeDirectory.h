#pragma once
#include "./FileSystem.h"

#include "../linkedList/LinkedList.h"
#include <iostream>
using namespace std;
FileSystem* FileSystem::changeDirectory(string& dirName) {
    if(dirName[0]=='/'||dirName[0]=='.'){
return this->findDirectoryPath(dirName);
    }
     else 
    {
        FileSystem* newDir = findDirectory(dirName);
        if (newDir) {
            cout << "Changed directory to: " << newDir->getName() << "\n";
            return newDir;
        } else {
            cout << "No such directory exists: " << dirName << "\n";
            return this; 
        }
    
}}
