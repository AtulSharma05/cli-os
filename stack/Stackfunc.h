#pragma once
#include <iostream>
#include "../linkedList/LinkedList.h"

template <typename T>
void Stack<T>::push(T value) {
    list.append(value);
}

template <typename T>
void Stack<T>::pop() {
    std::cout<<"popped";
    if (!list.isEmpty()) {
        // Pop the last element (since we're using append in LinkedList)
        list.remove(list.back());
    }
}

template <typename T>
T Stack<T>::top() {
    if (!list.isEmpty()) {
        return list.back();
    }
   // Handle empty stack case (throw an exception or return a default value)
}

template <typename T>
bool Stack<T>::isEmpty() {
    return list.isEmpty();
}
