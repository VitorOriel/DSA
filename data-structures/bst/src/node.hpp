#ifndef NODE_H
#define NODE_H

#include "namespace.hpp"

class BST::Node {
    friend class BinaryTree;
    friend class InorderIterator;

    public:
        Node(int item);
        ~Node();
    private:
        int data;
        Node* left;
        Node* right;
        Node* parent;
};

#endif