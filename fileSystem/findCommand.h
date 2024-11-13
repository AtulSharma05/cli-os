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
    FileSystem* tempDir=this->findDirectoryPath(path);
        if (type == "f") {
            Node<file>* cfile=tempDir->files.head;
            while(cfile!=nullptr){
                if(cfile->data.name==name||name=="\0"){

            tempDir->printWorkingDirectory();
            cout<<"/"<< cfile->data.name << endl;}
            cfile=cfile->next;

            }
           
            Node<FileSystem>* child=tempDir->children.head;
            string tempath=".";
                        while(child!=nullptr){
                        child->data.findCommand(tempath,type,name);
                        child = child->next;}

                        }
        if (type == "d") {
            Node<FileSystem>* dir=tempDir->children.head;
            while(dir!=nullptr){
                if(dir->data.name==name||name=="\0"){

            tempDir->printWorkingDirectory();
            cout<<"/"<< dir->data.name << endl;}
            dir=dir->next;

            }
           
            Node<FileSystem>* child=tempDir->children.head;
            string tempath=".";
                        while(child!=nullptr){
                        child->data.findCommand(tempath,type,name);
                        child = child->next;}

                        }                
                        }

