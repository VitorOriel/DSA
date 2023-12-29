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
class rb::InorderIterator {
    public:
        InorderIterator(rb::Node<T>* node);
        T next();
        inline bool hasNext() noexcept { return !this->stackIterator.empty(); }
    private:
        void pushLeftChildrens(rb::Node<T>* node);
        rb::Node<T>* currentNode;
        std::stack<rb::Node<T>*> stackIterator;
};

template<typename T>
rb::InorderIterator<T>::InorderIterator(rb::Node<T>* node) {
    if (node != nullptr)
        this->pushLeftChildrens(node);
}

template<typename T>
T rb::InorderIterator<T>::next() {
    rb::Node<T>* currentNode = this->stackIterator.top();
    this->stackIterator.pop();
    if (currentNode->right != nullptr)
        this->pushLeftChildrens(currentNode->right);
    return currentNode->data;
}

template<typename T>
void rb::InorderIterator<T>::pushLeftChildrens(rb::Node<T>* node) {
    while (node != nullptr) {
        this->stackIterator.push(node);
        node = node->left;
    }
}

#endif