
#pragma once
#include <string>

class Node {
    public:
        string name;
        bool isDirectory;
        Node* parent;
        Node* firstChild;
        Node* nextSibling;

        Node(string nodeName, bool isDir, Node* parentNode){
            name = nodeName;
            isDirectory = isDir;
            parent = parentNode;
        }
    };

class FileSystem {
private:
    

    Node* root;
    Node* currentDir;

public:
   FileSystem() {
    root = new Node("/", true, nullptr);
    currentDir = root;

}

FileSystem(const std::string& nodeName, bool isDir, Node* parentNode){
    root = new Node(nodeName, isDir, parentNode);
    currentDir = root;
    
}
    void createDirectory(string& dirName);
    void listFiles();
    void changeDirectory(string& dirName);
    void printWorkingDirectory();
};

