#pragma once
#include "FileSystem.h"
#include <iostream>
using namespace std;

void FileSystem::createDirectory(string& dirName) {
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
    cout << "Directory " << dirName << " created.\n";
}

void FileSystem::listFiles() {
    Node* temp = currentDir->firstChild;
    if (!temp) {
        cout << "No files or directories.\n";
    } else {
        while (temp) {
            cout << (temp->isDirectory ? "DIR " : "FILE ") << temp->name << endl;
            temp = temp->nextSibling;
        }
    }
}

void FileSystem::changeDirectory(string& dirName) {
    if (dirName == "..") {
        if (currentDir->parent) {
            currentDir = currentDir->parent;
        } else {
            cout << "Already at root directory.\n";
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
    cout << "Directory not found.\n";
}

void FileSystem::printWorkingDirectory() {
    Node* temp = currentDir;
    string path;
    while (temp) {
        path = "/" + temp->name + path;
        temp = temp->parent;
    }
    cout << "Current directory: " << path << endl;
}
