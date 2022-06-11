#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename T>
class Node {
    template<typename U>
    friend class List;

    public:
        Node(T item);
        ~Node();
    protected:
        T content;
        Node* previous;
        Node* next;
};

template<typename T>
Node<T>::Node(T item) {
    this->previous = nullptr;
    this->next = nullptr;
    this->content = item;
}

template<typename T>
Node<T>::~Node() {
    this->previous = nullptr;
    this->next = nullptr;
}

#endif