#include "CommandProcessor.h"
#include <iostream>

int main() {
    CommandProcessor cp;
    std::string command;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        } else if (command == "undo") {
            cp.undoCommand();
        } else if (command == "redo") {
            cp.redoCommand();
        } else if (command == "history") {
            cp.showHistory();
        } else {
            cp.executeCommand(command);
        }
    }

    return 0;
}
