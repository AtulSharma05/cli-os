#pragma once
#include "./FileSystem.h"
#include"hashing.h"
#include <iostream>
using namespace std;
template <>
void LinkedList<FileSystem>::append(FileSystem &value) {
    Node<FileSystem>* newNode = new Node<FileSystem>(value);
    if (isEmpty()) {
        head = newNode;
    } else {
        Node<FileSystem>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void FileSystem::makeDirectory(string& dirName) {
    FileSystem newDir(dirName,true,this);
     newDir.parent = this; 
    children.append(newDir);
    directoryMap.insert(dirName,newDir);
    
}

