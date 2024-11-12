
#pragma once
#include <string>
#include "../linkedList/LinkedList.h"
#include "./file.h"
using namespace std;

class FileSystem{
private:
    string name;
    LinkedList<FileSystem> children;
    LinkedList<file> files;
   bool isDirectory;
   FileSystem* parent;

public:
   FileSystem() : name("root"), isDirectory(true), parent(nullptr) {}
    FileSystem(string& dirName, bool isDir, FileSystem* parentDir)
        : name(dirName), isDirectory(isDir), parent(parentDir) {}


    void makeDirectory(string& dirName);
    FileSystem* findDirectoryPath(string& path);
    void listFiles();
    FileSystem* changeDirectory(string& dirName);
    void printWorkingDirectory();
    FileSystem* findDirectory(string&);
    void findCommand(string &path,string &type,string &name);
    void makeFile(string& fileName);
    file* findFile(string& fileName);
    string getName(){
       return name;
    }
    bool operator==(const FileSystem& other){
    return name == other.name;
}
bool operator!=(const FileSystem& other) const {
    return name != other.name;
}
void zipCommand(file * );
void unzipCommand(file * );
void zip(string filename){
   file *temp= this->findFile(filename);
   if(temp!=nullptr){
   this->zipCommand(temp);}
   else{cout<<"no such file exits";}
}
void unzip(string filename){
    file *temp= this->findFile(filename);
    if(temp!=nullptr){
   this->unzipCommand(temp);}
   else{cout<<"no such file exits";}
}
void nanoEditor(string& );
};

template <> 
void LinkedList<file>::display(){
    Node<file>* temp = head;
    while (temp != nullptr) {
        cout << temp->data.getName() << "\t";  // Print the file name
        temp = temp->next;
    }
    cout << endl;

}
template <>
void LinkedList<FileSystem>::display() {
    Node<FileSystem>* temp = head;
    while (temp != nullptr) {
       cout<<temp->data.getName();  // Call the FileSystem display method
        temp = temp->next;
    }
    cout << endl;
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
