#pragma once
#include "FileSystem.h"
#include "file.h"
#include"hashing.h"
#include <iostream>
using namespace std;
template <>
void LinkedList<file>::append(file &value) {
    Node<file>* newNode = new Node<file>(value);
    if (isEmpty()) {
        head = newNode;
    } else {
        Node<file>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void FileSystem::makeFile(string& filName) {
    file newFil(filName);

    files.append(newFil);
    fileMap.insert(filName, newFil);

}