
#pragma once
#include <string>
#include "../linkedList/LinkedList.h"
using namespace std;
class file{
    public:
string name;
int *content;
file(){
    
}
file(string name){
    this->name=name;
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