#pragma once
#include "CommandProcessor.h"
#include "../userManager/UserManager.h" 
#include "../userManager/UserManagerfunc.h" 
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/makeDirectory.h"
#include "../fileSystem/makeFile.h"
#include "../fileSystem/file.h"
#include "../fileSystem/findDirectory.h"
#include "../fileSystem/changeDirectory.h"
#include "../fileSystem/findDirectoryPath.h"
#include "../fileSystem/findCommand.h"
#include "../fileSystem/compress.h/map.h"
#include "../fileSystem/findFile.h"
#include "../fileSystem/nano.h"


#include <iostream>
#include <vector>


void CommandProcessor::processCommand(vector<UserManager>&users, string& command) {
    if(command.substr(0,5)=="find "){
    size_t pathStart = 5;
    size_t typePos = command.find(' ', pathStart);
    size_t namePos = command.find(' ', typePos + 1);
        string path = command.substr(pathStart, typePos - pathStart);
        string type = command.substr(typePos + 1, namePos - typePos - 1);
        string name = command.substr(namePos+1);

        // Validate the type
        if (type != "f" && type != "d") {
            cout << "Invalid type. Use 'f' for file or 'd' for directory." << endl;
            return;
        }

        // Use findCommand on the current directory
        currentDir->findCommand(path, type, name);
        
    }else 
    if (command == "ls") {
        currentDir->listFiles();

    } else if (command.substr(0, 6) == "mkdir ") {

        string dirName = command.substr(6);
        currentDir->makeDirectory(dirName);

    }else if (command.substr(0, 7) == "mkfile ") {

        string filName = command.substr(7);
        currentDir->makeFile(filName);

    } 
    else if (command.substr(0, 2) == "cd") {
        clearLines();
        if(command=="cd"){
            while(currentDir->parent!=nullptr){
                currentDir = currentDir->parent;
            }
        }else{


        string dirName = command.substr(3); 
        
      currentDir=currentDir->changeDirectory(dirName);}
    } else if (command == "pwd") {
        currentDir->printWorkingDirectory();
    } else if (command.substr(0, 8) == "adduser ") {
        string userInfo = command.substr(8);
        int spacePos = userInfo.find(' ');
        string username = userInfo.substr(0, spacePos);
        string password = userInfo.substr(spacePos + 1);
        UserManager newuser(username,password);
        users.push_back(newuser);
    } else if (command.substr(0, 4) == "zip ") {
        string filename = command.substr(4);
        currentDir->zip(filename);
    } else if (command.substr(0, 6) == "unzip ") {
        string filename = command.substr(6);
        currentDir->unzip(filename);
    } else if(command.substr(0,5)=="nano "){
        string filename = command.substr(5);
        currentDir->nanoEditor(filename);
    }
    else if (command.substr(0, 6) == "login ") {
        string userInfo = command.substr(6);
        int spacePos = userInfo.find(' ');
        string username = userInfo.substr(0, spacePos);
        string password = userInfo.substr(spacePos + 1);
        if (authenticateUser(users,username, password)) {
            cout << "Login successful.\n";
        } else {
            cout << "Login failed.\n";
        }
    } else if(command.substr(0,5)=="finds"){
        string name = command.substr(5 + 1);
        file* temp=currentDir->findFile(name);
        if(temp!=nullptr){
        cout<<temp->name;
        }else{ cout<<"No such file exits";
        }

    } else if (command.substr(0, 3) == "rm ") {
        string target = command.substr(3);
        if (currentDir->findFile(target)) {
            currentDir->removeFile(target);
            cout << "Removed file: " << target << "\n";
        } else if (currentDir->findDirectory(target)) {
            currentDir->removeNode(currentDir, target);
            cout << "Removed directory: " << target << "\n";
        } else {
            cout << "No such file or directory: " << target << "\n";
        }
    } else if (command.substr(0, 3) == "mv ") {
        size_t spacePos = command.find(' ', 3);
        string source = command.substr(3, spacePos - 3);
        string targetDirName = command.substr(spacePos + 1);
        FileSystem* targetDir = currentDir->findDirectory(targetDirName);
        if (currentDir->findFile(source)) {
            if (targetDir != nullptr) {
                currentDir->moveFile(source, targetDir);
                cout << "Moved file: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else if (currentDir->findDirectory(source)) {
            if (targetDir != nullptr) {
                currentDir->moveNode(currentDir, targetDir, source);
                cout << "Moved directory: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else {
            cout << "No such file or directory: " << source << "\n";
        }
    } else if (command.substr(0, 3) == "cp ") {
        size_t spacePos = command.find(' ', 3);
        string source = command.substr(3, spacePos - 3);
        string targetDirName = command.substr(spacePos + 1);
        FileSystem* targetDir = currentDir->findDirectory(targetDirName);
        if (currentDir->findFile(source)) {
            if (targetDir != nullptr) {
                currentDir->copyFile(source, targetDir);
                cout << "Copied file: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else if (currentDir->findDirectory(source)) {
            if (targetDir != nullptr) {
                currentDir->copyNode(currentDir, targetDir, source);
                cout << "Copied directory: " << source << "\n";
            } else {
                cout << "Target directory not found.\n";
            }
        } else {
            cout << "No such file or directory: " << source << "\n";
        }
    }
    else{
        cout << "Unknown command.\n";
    }
}
