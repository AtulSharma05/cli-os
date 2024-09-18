#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>

class UserManager {
private:
    struct UserNode {
        std::string username;
        std::string password;
        UserNode* next;

        UserNode(const std::string& user, const std::string& pass);
    };

    UserNode* head;

public:
    UserManager();
    void addUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
};

#endif // USERMANAGER_H
