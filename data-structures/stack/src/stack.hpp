/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include "node.hpp"
#include "exceptions.hpp"

template<typename T>
class Stack {
    public:
        Stack() { this->_Stack(); };
        Stack(const Stack<T>& other);
        ~Stack() { while(!this->isEmpty()) this->pop(); }
        void push(T item);
        T pop();
        inline bool isEmpty() { return this->top == nullptr; }
    private:
        void _Stack();
        Node<T>* top;
        size_t size;
};

template<typename T>
void Stack<T>::_Stack() {
    this->top = nullptr;
    this->size = 0;
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
    this->_Stack();
    Stack<T> tempStack = Stack<T>();
    Node<T>* crawlNode = other.top;
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
        newNode->next = this->top;
    this->top = newNode;
    this->size += 1;
}

template<typename T>
T Stack<T>::pop() {
    if (!this->isEmpty()) {
        Node<T>* popNode = this->top;
        this->top = this->top->next;
        T popItem = popNode->data;
        this->size -= 1;
        delete popNode;
        return popItem;
    }
    throw EmptyStackException("Cannot pop from an empty stack");
}

#endif