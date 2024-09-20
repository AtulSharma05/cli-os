#pragma once
#include "CommandProcessor.h"
#include <iostream>

void CommandProcessor::processCommand(vector<UserManager>& users, const std::string& command) {
    if (command == "ls") {
        fileSystem->listFiles();
    } else if (command.substr(0, 6) == "mkdir ") {
        std::string dirName = command.substr(6);
        fileSystem->createDirectory(dirName);
    } else if (command.substr(0, 3) == "cd ") {
        std::string dirName = command.substr(3);
        fileSystem->changeDirectory(dirName);
    } else if (command == "pwd") {
        fileSystem->printWorkingDirectory();
    } else if (command.substr(0, 7) == "adduser ") {
        std::string userInfo = command.substr(8);
        size_t spacePos = userInfo.find(' ');
        std::string username = userInfo.substr(0, spacePos);
        std::string password = userInfo.substr(spacePos + 1);
        UserManager newuser(username,password);
        users.push_back(newuser);
    } else if (command.substr(0, 8) == "login ") {
        std::string userInfo = command.substr(6);
        size_t spacePos = userInfo.find(' ');
        std::string username = userInfo.substr(0, spacePos);
        std::string password = userInfo.substr(spacePos + 1);
        if (users->authenticateUser(users,username, password)) {
            std::cout << "Login successful.\n";
        } else {
            std::cout << "Login failed.\n";
        }
    } else {
        std::cout << "Unknown command.\n";
    }
}
