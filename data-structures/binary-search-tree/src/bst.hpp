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
        BST::InorderIterator begin() { return BST::InorderIterator(this->root); }
    private:
        void destroyRecursive(BST::Node* node);
        BST::Node* insert(BST::Node* node, int data);
        BST::Node* searchNode(int data);
        void transplant(BST::Node* old, BST::Node* new_);
        BST::Node* min(BST::Node* subTreeRoot);
        BST::Node* max(BST::Node* subTreeRoot);
        BST::Node* root;
};

#endif