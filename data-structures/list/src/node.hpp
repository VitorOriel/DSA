/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
class Node {
    template<typename U>
    friend class List;

    public:
        Node(T item);
        ~Node();
    private:
        T data;
        Node* pPrevious;
        Node* next;
};

template<typename T>
Node<T>::Node(T item) {
    this->pPrevious = nullptr;
    this->next = nullptr;
    this->data = item;
}

template<typename T>
Node<T>::~Node() {
    this->pPrevious = nullptr;
    this->next = nullptr;
}

#endif