#pragma once
#include <iostream>
using namespace std;

class UserManager {
private:
  int userId;
    string userName;
    string userPassword;


public:
    UserManager(){
        userId = 0;
        userName = "root";
        userPassword = "admin";
    }
    UserManager(string name,string pwd){
    userId++;
    userName = name;
    userPassword = pwd;
}
//    bool authenticateUser(vector<UserManager>&,string , const string& );
   string getName(){
    return userName;
   };
   string getPassword(){
    return userPassword;
   };
   int getUserId(){
    return userId;
   }

};

