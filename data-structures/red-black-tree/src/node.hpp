/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef NODE_HPP
#define NODE_HPP

#include "namespace.hpp"

template<typename T>
class rb::Node {
    template<typename U>
    friend class rb::RedBlackTree;
    template<typename V>
    friend class rb::InorderIterator;

    public:
        Node(const T& data);
        ~Node();
    private:
        T data;
        rb::Color color;
        Node* left;
        Node* right;
        Node* parent;
};

template<typename T>
rb::Node<T>::Node(const T& data) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = data;
    this->color = rb::BLACK;
}

template<typename T>
rb::Node<T>::~Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

#endif