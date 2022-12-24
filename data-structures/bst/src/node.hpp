#ifndef NODE_H
#define NODE_H

#include "bst.hpp"

class BinaryTree::Node {
    friend class BinaryTree;

    public:
        Node(int item);
        ~Node();
    private:
        int data;
        Node* left;
        Node* right;
        Node* parent;
};

BinaryTree::Node::Node(int item) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = item;
}

BinaryTree::Node::~Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

#endif