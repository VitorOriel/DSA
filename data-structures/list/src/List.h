#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Node.h"
using namespace std;

template<typename T>
class List {
    public:
        List();
        ~List();
        void append(T item);
        void remove(T item);
        void print();
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
};

template<typename T>
List<T>::List() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template<typename T>
List<T>::~List() {
    Node<T>* thisNode = this->head;
    while (thisNode != nullptr) {
        Node<T>* nodeAux = thisNode;
        thisNode = thisNode->next;
        delete nodeAux;
    }
}

template<typename T>
void List<T>::append(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (this->head == nullptr)
        this->head = newNode;
    else
        this->tail->next = newNode;
    this->tail = newNode;
    this->size += 1;
}

template<typename T>
void List<T>::print() {
    Node<T>* thisNode = this->head;
    while (thisNode != nullptr) {
        cout << to_string(thisNode->content) << ' ';
        thisNode = thisNode->next;
    }
    cout << endl;
}

#endif