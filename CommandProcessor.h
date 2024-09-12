#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>

class CommandProcessor {
public:
    void redoCommand();
    void undoCommand();
    void executeCommand(const std::string& command);
    void showHistory() const;
private:
    // Private members
};

#endif // COMMANDPROCESSOR_H
