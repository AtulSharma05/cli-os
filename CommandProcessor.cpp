#include "CommandProcessor.h"
#include <iostream>

void CommandProcessor::redoCommand() {
    // Implementation here
     std::cout<<"redo";
}

void CommandProcessor::undoCommand() {
    // Implementation here
    std::cout<<"undo";
}

void CommandProcessor::executeCommand(const std::string& command) {
    // Implementation here
     std::cout<<command;
}

void CommandProcessor::showHistory() const {
    // Implementation here
     std::cout<<"uhistory";
}
