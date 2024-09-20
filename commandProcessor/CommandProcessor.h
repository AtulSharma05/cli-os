

#include <string>
#include "../userManager/UserManager.h"
#include "../fileSystem/FileSystem.h"

class CommandProcessor {
private:
    FileSystem *fileSystem;

public:
    CommandProcessor(){
        // Initialize the user manager and file system
        fileSystem = new  FileSystem();

    };
    void processCommand(vector<UserManager>&,const std::string& command);
};

