
#pragma once
#include <string>
#include "../linkedList/LinkedList.h"
using namespace std;
class file{
    public:
string name;
string content;

  file(){ }
    file(string name) 
        : name(name) {}
void setcontent(string c){
    content=c;

}
string getName(){
    return name;
}
bool operator==(const file& other){
    return name == other.name;
}
bool operator!=(const file& other){
    return name != other.name;
}
void display(){
    cout<<name;
}

};