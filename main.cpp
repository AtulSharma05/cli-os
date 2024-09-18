#include "CommandProcessor.h"
#include <iostream>

int main() {
    CommandProcessor cp;
    std::string command;

    std::cout << "Welcome to the CLI Operating System.\n";
    std::cout << "Type 'exit' to quit.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        cp.processCommand(command);
    }

    return 0;
}
