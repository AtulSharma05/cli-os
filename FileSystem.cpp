#include "FileSystem.h"
#include <iostream>

FileSystem::FileSystem() {
    root = new Node("/", true, nullptr);
    currentDir = root;
}

FileSystem::Node::Node(const std::string& nodeName, bool isDir, Node* parentNode)
    : name(nodeName), isDirectory(isDir), parent(parentNode), firstChild(nullptr), nextSibling(nullptr) {}

void FileSystem::createDirectory(const std::string& dirName) {
    Node* newDir = new Node(dirName, true, currentDir);
    if (!currentDir->firstChild) {
        currentDir->firstChild = newDir;
    } else {
        Node* temp = currentDir->firstChild;
        while (temp->nextSibling) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = newDir;
    }
    std::cout << "Directory " << dirName << " created.\n";
}

void FileSystem::listFiles() {
    Node* temp = currentDir->firstChild;
    if (!temp) {
        std::cout << "No files or directories.\n";
    } else {
        while (temp) {
            std::cout << (temp->isDirectory ? "DIR " : "FILE ") << temp->name << std::endl;
            temp = temp->nextSibling;
        }
    }
}

void FileSystem::changeDirectory(const std::string& dirName) {
    if (dirName == "..") {
        if (currentDir->parent) {
            currentDir = currentDir->parent;
        } else {
            std::cout << "Already at root directory.\n";
        }
        return;
    }

    Node* temp = currentDir->firstChild;
    while (temp) {
        if (temp->isDirectory && temp->name == dirName) {
            currentDir = temp;
            return;
        }
        temp = temp->nextSibling;
    }
    std::cout << "Directory not found.\n";
}

void FileSystem::printWorkingDirectory() {
    Node* temp = currentDir;
    std::string path;
    while (temp) {
        path = "/" + temp->name + path;
        temp = temp->parent;
    }
    std::cout << "Current directory: " << path << std::endl;
}
