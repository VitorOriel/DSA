/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef NODE_HPP
#define NODE_HPP

#include "namespace.hpp"

template<typename T>
class avl::Node {
    template<typename U>
    friend class avl::AVLTree;
    template<typename V>
    friend class avl::InorderIterator;

    public:
        Node(const T& data);
        ~Node();
    private:
        T data;
        size_t height;
        Node* left;
        Node* right;
        Node* parent;
};

template<typename T>
avl::Node<T>::Node(const T& data) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = data;
    this->height = 1;
}

template<typename T>
avl::Node<T>::~Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

#endif