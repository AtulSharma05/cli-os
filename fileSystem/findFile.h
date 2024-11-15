#pragma once
#include "./FileSystem.h"
#include "../linkedList/LinkedList.h"
#include <iostream>
using namespace std;
//    file* FileSystem::findFile(string& fileName) {
//     Node<file>* temp = files.head; 

//     while (temp != nullptr) {
//         if (temp->data.getName() == fileName) { 
//             return &temp->data; 
//         }
//         temp = temp->next;
//     }
//     return nullptr;
// }
file* FileSystem::findFile(string& fileName){
       
        for (auto node = fileCache.head; node != nullptr; node = node->next) {
            if (node->data->getName() == fileName) {
                return node->data;
            }
        }
        file* f = fileMap.search(fileName);
        if (f) {
            this->updatefCache(fileCache, f);
            return f;
        }
        return nullptr;
    }
