/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef NODE_HPP
#define NODE_HPP

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