/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "Node.h"
#include "EmptyStackException.h"

template<typename T>
class Stack {
    public:
        Stack() { this->_Stack(); };
        Stack(const Stack<T>& other);
        ~Stack() { while(!this->isEmpty()) this->pop(); }
        void push(T item);
        T pop();
        inline bool isEmpty() { return this->pTop == nullptr; }
    private:
        void _Stack();
        Node<T>* pTop;
        size_t size;
};

template<typename T>
void Stack<T>::_Stack() {
    this->pTop = nullptr;
    this->size = 0;
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
    this->_Stack();
    Stack<T> tempStack = Stack<T>();
    Node<T>* crawlNode = other.pTop;
    while (crawlNode != nullptr) {
        tempStack.push(crawlNode->data);
        crawlNode = crawlNode->next;
    }
    while (!tempStack.isEmpty())
        this->push(tempStack.pop());
}

template<typename T>
void Stack<T>::push(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (!this->isEmpty())
        newNode->next = this->pTop;
    this->pTop = newNode;
    this->size += 1;
}

template<typename T>
T Stack<T>::pop() {
    if (!this->isEmpty()) {
        Node<T>* popNode = this->pTop;
        this->pTop = this->pTop->next;
        T popItem = popNode->data;
        this->size -= 1;
        delete popNode;
        return popItem;
    }
    throw EmptyStackException("Cannot pop from an empty stack");
}

#endif