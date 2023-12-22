/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stack>
#include "namespace.hpp"
#include "node.hpp"

template<typename T>
class avl::InorderIterator {
    public:
        InorderIterator(avl::Node<T>* node);
        T& next();
        inline bool hasNext() noexcept { return !this->stackIterator.empty(); }
    private:
        void pushLeftChildrens(avl::Node<T>* node);
        avl::Node<T>* currentNode;
        std::stack<avl::Node<T>*> stackIterator;
};

template<typename T>
avl::InorderIterator<T>::InorderIterator(avl::Node<T>* node) {
    if (node != nullptr)
        this->pushLeftChildrens(node);
}

template<typename T>
T& avl::InorderIterator<T>::next() {
    avl::Node<T>* currentNode = this->stackIterator.top();
    this->stackIterator.pop();
    if (currentNode->right != nullptr)
        this->pushLeftChildrens(currentNode->right);
    return currentNode->data;
}

template<typename T>
void avl::InorderIterator<T>::pushLeftChildrens(avl::Node<T>* node) {
    while (node != nullptr) {
        this->stackIterator.push(node);
        node = node->left;
    }
}

#endif