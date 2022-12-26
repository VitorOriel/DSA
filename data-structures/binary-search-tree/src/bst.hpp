/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "namespace.hpp"
#include "node.hpp"
#include "iterator.hpp"

class BST::BinarySearchTree {
    public:
        BinarySearchTree() { this->root = nullptr; }
        ~BinarySearchTree() { this->destroyRecursive(this->root); }
        void insert(int data);
        int search(int data);
        void remove(int data);
        int min();
        int max();
        InorderIterator begin() { return InorderIterator(this->root); }
    private:
        void destroyRecursive(Node* node);
        Node* insert(Node* node, int data);
        Node* searchNode(int data);
        void transplant(Node* old, Node* new_);
        Node* min(Node* subTreeRoot);
        Node* max(Node* subTreeRoot);
        Node* root;
};

#endif