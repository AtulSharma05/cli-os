#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include "UserManager.h"
#include "FileSystem.h"

class CommandProcessor {
private:
    UserManager userManager;
    FileSystem fileSystem;

public:
    CommandProcessor();
    void processCommand(const std::string& command);
};

#endif // COMMANDPROCESSOR_H
