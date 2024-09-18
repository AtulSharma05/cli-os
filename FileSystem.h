#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>

class FileSystem {
private:
    struct Node {
        std::string name;
        bool isDirectory;
        Node* parent;
        Node* firstChild;
        Node* nextSibling;

        Node(const std::string& nodeName, bool isDir, Node* parentNode);
    };

    Node* root;
    Node* currentDir;

public:
    FileSystem();
    void createDirectory(const std::string& dirName);
    void listFiles();
    void changeDirectory(const std::string& dirName);
    void printWorkingDirectory();
};

#endif // FILESYSTEM_H
