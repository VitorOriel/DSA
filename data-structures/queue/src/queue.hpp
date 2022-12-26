/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include "node.hpp"
#include "exceptions.hpp"

template<typename T>
class Queue {
    public:
        Queue() { this->_Queue(); }
        Queue(const Queue<T>& other);
        ~Queue() { while(!this->isEmpty()) this->dequeue(); }
        void enqueue(T item);
        T dequeue();
        inline bool isEmpty() { return this->front == nullptr; }
    private:
        void _Queue(); // Base constructor
        Node<T>* back;
        Node<T>* front;
        size_t size;
};  

template<typename T>
void Queue<T>::_Queue() {
    this->back = nullptr;
    this->front = nullptr;
    this->size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
    this->_Queue();
    Node<T>* crawlNode = other.front;
    while (crawlNode != nullptr) {
        this->enqueue(crawlNode->data);
        crawlNode = crawlNode->next;
    }
}

template<typename T>
void Queue<T>::enqueue(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (this->isEmpty())
        this->front = newNode;
    else
        this->back->next = newNode;
    this->back = newNode;
    this->size += 1;
}

template<typename T>
T Queue<T>::dequeue() {
    if (!this->isEmpty()) {
        Node<T>* dequeuedNode = this->front;
        this->front = this->front->next;
        this->size -= 1;
        T dequeuedData = dequeuedNode->data;
        delete dequeuedNode;
        return dequeuedData;
    }
    throw EmptyQueueException("Can't dequeue from an empty queue");
}

#endif