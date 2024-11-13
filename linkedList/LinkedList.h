#pragma once
#include <iostream>
#include <vector>
#include <string>
template <typename T>
class Node {
    public:
        T data;
        Node* next;
        Node(T value) { 
        data=value;
        next=nullptr; }
        Node(T *value){
            data=*value;
            next=nullptr;
        }
    };
template <typename T>
class LinkedList {

public:
    Node<T>* head;

    LinkedList(){
        head = nullptr;
    }
    ~LinkedList();
    void append(T &);
   void appends(T *);
    void remove(T );
    void display();
    bool isEmpty();
    void ls();
    int size();
    T& back(); // Method to get the last element
    
};

#include "LinkedListfunc.h" // Include implementation here