#pragma once
#include "../linkedList/LinkedList.h"

template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    void push(T value);
    void pop();
    T top();
    bool isEmpty();
   
};

#include "Stackfunc.h"

