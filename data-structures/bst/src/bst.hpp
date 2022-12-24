#ifndef BST_H
#define BST_H

#include "node.hpp"

class BinaryTree {
    public:
        BinaryTree();
        ~BinaryTree();
        void insert(int data);
        int search(int data);
        int min();
        int max();
    private:
        Node* insert(Node* node, int data);
        Node* searchNode(int data);
        Node* min(Node* subTreeRoot);
        Node* max(Node* subTreeRoot);
        Node* root;
};

#endif