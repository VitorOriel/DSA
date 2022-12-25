#include "node.hpp"

BST::Node::Node(int item) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = item;
}

BST::Node::~Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}