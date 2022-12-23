#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include "Node.h"
#include "EmptyQueueException.h"

template<typename T>
class Queue {
    public:
        Queue() { this->_Queue(); }
        Queue(const Queue<T>& other);
        ~Queue() { while(!this->isEmpty()) this->dequeue(); }
        void enqueue(T item);
        T dequeue();
        inline bool isEmpty() { return this->pFront == nullptr; }
    private:
        void _Queue(); // Base constructor
        Node<T>* pBack;
        Node<T>* pFront;
        size_t size;
};  

template<typename T>
void Queue<T>::_Queue() {
    this->pBack = nullptr;
    this->pFront = nullptr;
    this->size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
    this->_Queue();
    Node<T>* crawlNode = other.pFront;
    while (crawlNode != nullptr) {
        this->enqueue(crawlNode->data);
        crawlNode = crawlNode->next;
    }
}

template<typename T>
void Queue<T>::enqueue(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (this->isEmpty())
        this->pFront = newNode;
    else
        this->pBack->next = newNode;
    this->pBack = newNode;
    this->size += 1;
}

template<typename T>
T Queue<T>::dequeue() {
    if (!this->isEmpty()) {
        Node<T>* dequeuedNode = this->pFront;
        this->pFront = this->pFront->next;
        this->size -= 1;
        T dequeuedData = dequeuedNode->data;
        delete dequeuedNode;
        return dequeuedData;
    }
    throw EmptyQueueException("Can't dequeue from an empty queue");
}

#endif