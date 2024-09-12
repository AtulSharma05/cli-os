#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    void push(T value);
    void pop();
    T top() const;
    bool isEmpty() const;
};

#include "Stack.cpp"
#endif // STACK_H
