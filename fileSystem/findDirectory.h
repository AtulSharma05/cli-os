#pragma once
#include "./FileSystem.h"
#include "../linkedList/LinkedList.h"
#include <iostream>
using namespace std;

FileSystem* FileSystem::findDirectory(string& dirName) {
    if (this->name == dirName && this->isDirectory) {
        return this;
    }
    Node<FileSystem>* temp = children.head;
    while (temp != nullptr) {
        FileSystem* result = temp->data.findDirectory(dirName);
        if (result != nullptr) {
            return result; // Found the directory
        }
        temp = temp->next;
    }

    return nullptr; // Not found
}