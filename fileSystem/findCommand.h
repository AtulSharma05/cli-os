#pragma once
#include "./FileSystem.h"
#include "../fileSystem/findDirectoryPath.h"
#include "../linkedList/LinkedList.h"
#include "../fileSystem/findDirectory.h"
#include "../fileSystem/changeDirectory.h"
#include "../fileSystem/findDirectoryPath.h"
#include "../fileSystem/findCommand.h"
#include <iostream>
using namespace std;

void FileSystem::findCommand(string &path,string &type,string &name) {
    FileSystem* tempDir=findDirectoryPath(path);
        if (type == "f") {
            Node<file>* cfile=tempDir->files.head;
            while(cfile!=nullptr){
                if(cfile->data.name==name){

            tempDir->printWorkingDirectory();
            cout<<"/"<< cfile->data.name << endl;}
            cfile=cfile->next;

            }
           }
            Node<FileSystem>* child=tempDir->children.head;
            string tempath=".";
                        while(child!=nullptr){
                        child->data.findCommand(tempath,type,name);
                        child = child->next;

                        }}

            //         }}
            // else if (type == "directory") {
            //             if (root.find(name) != root.end()) {
            //                 cout << "Directory found in root directory" << endl;
            //                 } else {
            //                     cout << "Directory not found in root directory" << endl;
            //                     }
            //                     } else {
            //                         cout << "Invalid type" << endl;
            //                         }

