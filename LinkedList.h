#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList();
    ~LinkedList();
    void append(T value);
    void remove(T value);
    void display() const;
    bool isEmpty() const;
    T& back(); // Method to get the last element
};

#include "LinkedList.cpp" // Include implementation here

#endif // LINKEDLIST_H
