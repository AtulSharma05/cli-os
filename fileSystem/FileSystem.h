
#pragma once
#include <string>
#include "../linkedList/LinkedList.h"
#include "./file.h"

class FileSystem{
private:
    string name;
    LinkedList<FileSystem> children;
    LinkedList<file> files;
   bool isDirectory;

public:
FileSystem() : name(""), isDirectory(true) {}
FileSystem(const std::string& dirName, bool isDir)
        : name(dirName), isDirectory(isDir) {}

    void makeDirectory(string& dirName);
    void listFiles();
    void changeDirectory(string& dirName);
    void printWorkingDirectory();
    void makeFile(string& fileName);
    void display(){
        cout<< name << endl;
    }
    bool operator==(const FileSystem& other){
    return name == other.name;
}
bool operator!=(const FileSystem& other) const {
    return name != other.name;
}

};

template <> 
void LinkedList<file>::display(){
    Node<file>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data.getName() << " ";  // Print the file name
        temp = temp->next;
    }
    std::cout << std::endl;

}
template <>
void LinkedList<FileSystem>::display() {
    Node<FileSystem>* temp = head;
    while (temp != nullptr) {
        temp->data.display();  // Call the FileSystem display method
        temp = temp->next;
    }
    std::cout << std::endl;
}


template <>
void LinkedList<FileSystem>::remove(FileSystem value) {
    if (isEmpty()) return;

    // Remove head if it matches
    if (head->data == value) {
        Node<FileSystem>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<FileSystem>* current = head;
    while ((current->next != nullptr) && (current->next->data != value)) {
        current = current->next;
    }

    // If found, remove the node
    if (current->next != nullptr) {
        Node<FileSystem>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}
template <>
void LinkedList<file>::remove(file value) {
    if (isEmpty()) return;

    // Remove head if it matches
    if (head->data == value) {
        Node<file>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<file>* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    // If found, remove the node
    if (current->next != nullptr) {
        Node<file>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}