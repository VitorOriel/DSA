/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef NODE_H
#define NODE_H

#include "namespace.hpp"

class BST::Node {
    friend class BinarySearchTree;
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