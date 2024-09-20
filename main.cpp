#include "./commandProcessor/CommandProcessor.h"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    UserManager root;
   vector<UserManager> users;
   users.push_back(root);
string command;
CommandProcessor cp;
    std::cout << "Welcome to the CLI Operating System.\n";
    std::cout << "Type 'exit' to quit.\n";
    std::cout << "Type 'help' for a list of available commands.\n";

    while (true) {
        std::cout << "> ";

        if (command == "exit") {
            break;
        }
cp.processCommand(users,command);
    }

    return 0;
}
