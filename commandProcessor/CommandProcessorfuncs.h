#pragma once
#include "CommandProcessor.h"
#include "../userManager/UserManager.h" 
#include "../userManager/UserManagerfunc.h" 
#include "../fileSystem/FileSystem.h"
#include "../fileSystem/makeDirectory.h"
#include "../fileSystem/makeFile.h"
#include <iostream>
#include <vector>


void CommandProcessor::processCommand(vector<UserManager>&users, string& command) {
    
    if (command == "ls") {
cout<<"ls command executed";
        fileSystem->listFiles();

    } else if (command.substr(0, 6) == "mkdir ") {
        cout<<"mkdir command executed";

        string dirName = command.substr(6);
        fileSystem->makeDirectory(dirName);

    }else if (command.substr(0, 7) == "mkfile ") {
        cout<<"mkfile command executed";

        string filName = command.substr(7);
        fileSystem->makeFile(filName);

    } 
    else if (command.substr(0, 3) == "cd ") {
        cout<<"cd command executed";
        string dirName = command.substr(3);
        fileSystem->changeDirectory(dirName);
    } else if (command == "pwd") {
        fileSystem->printWorkingDirectory();
    } else if (command.substr(0, 7) == "adduser ") {
        string userInfo = command.substr(8);
        int spacePos = userInfo.find(' ');
        string username = userInfo.substr(0, spacePos);
        string password = userInfo.substr(spacePos + 1);
        UserManager newuser(username,password);
        users.push_back(newuser);
    } else if (command.substr(0, 8) == "login ") {
        string userInfo = command.substr(6);
        int spacePos = userInfo.find(' ');
        string username = userInfo.substr(0, spacePos);
        string password = userInfo.substr(spacePos + 1);
        if (authenticateUser(users,username, password)) {
            cout << "Login successful.\n";
        } else {
            cout << "Login failed.\n";
        }
    } else {
        cout << "Unknown command.\n";
    }
}
