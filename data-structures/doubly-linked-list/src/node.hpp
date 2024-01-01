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
        Node(const T& item);
        ~Node();
    private:
        T data;
        Node* previous;
        Node* next;
};

template<typename T>
Node<T>::Node(const T& item) {
    this->previous = nullptr;
    this->next = nullptr;
    this->data = item;
}

template<typename T>
Node<T>::~Node() {
    this->previous = nullptr;
    this->next = nullptr;
}

#endif