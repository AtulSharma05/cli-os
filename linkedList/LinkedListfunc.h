#pragma once
#include "LinkedList.h"
#include <iostream>




template <typename T>
LinkedList<T>::~LinkedList() {
    while (!isEmpty()) {
        remove(head->data);
    }
}

template <typename T>
void LinkedList<T>::append(T &value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = newNode;
    } else {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


template <typename T>
void LinkedList<T>::remove(T value) {
    if (isEmpty()) return;
    if (head->data == value) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node<T>* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}



template <typename T>
void LinkedList<T>::display() {
    Node<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <typename T>
bool LinkedList<T>::isEmpty(){
    return head == nullptr;
}

template <typename T>
T& LinkedList<T>::back() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    Node<T>* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->data;
}



