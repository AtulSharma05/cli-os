#include "UserManager.h"
#include <iostream>

UserManager::UserManager() : head(nullptr) {}

UserManager::UserNode::UserNode(const std::string& user, const std::string& pass)
    : username(user), password(pass), next(nullptr) {}

void UserManager::addUser(const std::string& username, const std::string& password) {
    UserNode* newUser = new UserNode(username, password);
    if (!head) {
        head = newUser;
    } else {
        UserNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newUser;
    }
    std::cout << "User " << username << " added.\n";
}

bool UserManager::authenticateUser(const std::string& username, const std::string& password) {
    UserNode* temp = head;
    while (temp) {
        if (temp->username == username && temp->password == password) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
