#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "namespace.hpp"
#include "node.hpp"
#include "iterator.hpp"

class BST::BinaryTree {
    public:
        BinaryTree();
        ~BinaryTree();
        void insert(int data);
        int search(int data);
        int min();
        int max();
        InorderIterator begin() { return InorderIterator(this->root); }
    private:
        Node* insert(Node* node, int data);
        Node* searchNode(int data);
        Node* min(Node* subTreeRoot);
        Node* max(Node* subTreeRoot);
        Node* root;
};

#endif