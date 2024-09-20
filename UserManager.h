#pragma once
#include "UserManager.h"
#include <iostream>
#include<string>
#include <vector>

bool  authenticateUser( vector<UserManager>& users,string name, const std::string& password) {
   
   for (int i = 0; i < users.size(); i++) {
    if (users[i].getName() == name && users[i].getPassword() == password)
    return true;
    }
    return false;
}
