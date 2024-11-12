#pragma once
#include "./FileSystem.h"
#include "../linkedList/LinkedList.h"
#include <iostream>
using namespace std;
   file* FileSystem::findFile(string& fileName) {
    Node<file>* temp = files.head; // Assuming LinkedList has a 'head' pointer for the start

    while (temp != nullptr) {
        if (temp->data.getName() == fileName) { // Assuming file has a getName() method
            return &temp->data; // Return a pointer to the file if found
        }
        temp = temp->next;
    }
    return nullptr; // Return nullptr if the file is not found
}

