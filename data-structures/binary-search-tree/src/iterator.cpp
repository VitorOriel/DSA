/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#include "iterator.hpp"

BST::InorderIterator::InorderIterator(BST::Node* node) {
    if (node != nullptr)
        this->pushLeftChildrens(node);
}

int BST::InorderIterator::next() {
    BST::Node* currentNode = this->stackIterator.top();
    this->stackIterator.pop();
    if (currentNode->right != nullptr)
        this->pushLeftChildrens(currentNode->right);
    return currentNode->data;
}

void BST::InorderIterator::pushLeftChildrens(BST::Node* node) {
    while (node != nullptr) {
        this->stackIterator.push(node);
        node = node->left;
    }
}