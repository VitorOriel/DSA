/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stack>
#include "namespace.hpp"
#include "node.hpp"

class BST::InorderIterator {
    public:
        InorderIterator(BST::Node* node);
        int next();
        inline bool hasNext() noexcept { return !this->stackIterator.empty(); }
    private:
        void pushLeftChildrens(BST::Node* node);
        BST::Node* currentNode;
        std::stack<BST::Node*> stackIterator;
};

#endif