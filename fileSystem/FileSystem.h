
#pragma once
#include <string>
#include "../linkedList/LinkedList.h"
#include"hashing.h"
#include "./file.h"
using namespace std;

class FileSystem{
public:
    string name;
    LinkedList<FileSystem> children;
    LinkedList<file> files;
   bool isDirectory;
   FileSystem* parent;
   Hashing<string, FileSystem> directoryMap;
    Hashing<string, file> fileMap;
    LinkedList<FileSystem*> directoryCache;
    LinkedList<file*> fileCache;
 int maxCacheSize = 5;

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
 void updatefCache(LinkedList<file*>& fileCache, file* item) {
        fileCache.remove(item);
        fileCache.append(item);

        if (fileCache.size() > maxCacheSize) {
            fileCache.remove(fileCache.back());
        }
    }
     void updatedCache(LinkedList<FileSystem*>& directoryCache, FileSystem* item) {
        directoryCache.remove(item);
        directoryCache.append(item);

        if (directoryCache.size() > maxCacheSize) {
            directoryCache.remove(directoryCache.back());
        }
    }
void removeNode(FileSystem* parent,  string& name);
bool moveNode(FileSystem* sourceDir, FileSystem* targetDir,  string& name);
bool copyNode(FileSystem* sourceDir, FileSystem* targetDir, string& name);
void removeFile(string& fileName);
void moveFile(string& fileName, FileSystem* targetDir);
void copyFile(string& fileName, FileSystem* targetDir);
};

template <> 
void LinkedList<file>::display(){
    Node<file>* temp = head;
    while (temp != nullptr) {
        cout << temp->data.getName() << " ";  // Print the file name
        temp = temp->next;
    }
    cout << endl;

}
template <>
void LinkedList<FileSystem>::display() {
    Node<FileSystem>* temp = head;
    while (temp != nullptr) {
       cout<<temp->data.getName()<<" ";  // Call the FileSystem display method
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
    }}
template <>
void LinkedList<file>::appends(file *value) {
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
template <>
void LinkedList<FileSystem>::appends(FileSystem *value) {
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


void FileSystem::removeNode(FileSystem* parent, string& name) {
    FileSystem* dirToRemove = findDirectory(name);
    if (dirToRemove != nullptr && dirToRemove->parent == parent) {
        parent->children.remove(*dirToRemove);
        directoryMap.remove(name);
    }
}

bool FileSystem::moveNode(FileSystem* sourceDir, FileSystem* targetDir, string& name) {
    FileSystem* dirToMove = findDirectory(name);
    if (dirToMove != nullptr && dirToMove->parent == sourceDir) {
        sourceDir->children.remove(*dirToMove);
        targetDir->children.appends(dirToMove);
        dirToMove->parent = targetDir;
        directoryMap.remove(name);
        directoryMap.insert(name, *dirToMove);
        return true;
    }
    return false;
}

bool FileSystem::copyNode(FileSystem* sourceDir, FileSystem* targetDir, string& name) {
    FileSystem* dirToCopy = findDirectory(name);
    if (dirToCopy != nullptr && dirToCopy->parent == sourceDir) {
        FileSystem* copiedDir = new FileSystem(*dirToCopy);
        targetDir->children.appends(copiedDir);
        copiedDir->parent = targetDir;
        directoryMap.insert(name, *copiedDir);
        return true;
    }
    return false;
}

void FileSystem::removeFile(string& fileName) {
    file* f = findFile(fileName);
    if (f != nullptr) {
        files.remove(*f);
        fileMap.remove(fileName);
    }
}

void FileSystem::moveFile(string& fileName, FileSystem* targetDir) {
    file* f = findFile(fileName);
    if (f != nullptr) {
        files.remove(*f);
        targetDir->files.appends(f);
        fileMap.remove(fileName);
        targetDir->fileMap.insert(fileName, *f);
    }
}

void FileSystem::copyFile(string& fileName, FileSystem* targetDir) {
    file* f = findFile(fileName);
    if (f != nullptr) {
        file* copiedFile = new file(*f);
        targetDir->files.appends(copiedFile);
        targetDir->fileMap.insert(fileName, *copiedFile);
    }
}
