/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "namespace.hpp"
#include "node.hpp"
#include "iterator.hpp"
#include "exceptions.hpp"

template<typename T = rb::BaseData>
class rb::RedBlackTree {
    public:
        RedBlackTree() { this->root = nullptr; }
        ~RedBlackTree() { this->destroyRecursive(this->root); }
        void insert(const T& data);
        T& search(const T& data);
        void remove(const T& data);
        T& min();
        T& max();
        rb::InorderIterator<T> begin() { return rb::InorderIterator<T>(this->root); }
    private:
        void destroyRecursive(rb::Node<T>* node);
        rb::Node<T>* insert(rb::Node<T>* node, const T& data);
        rb::Node<T>* searchNode(const T& data);
        void transplant(rb::Node<T>* old, rb::Node<T>* new_);
        rb::Node<T>* min(rb::Node<T>* subTreeRoot);
        rb::Node<T>* max(rb::Node<T>* subTreeRoot);
        rb::Node<T>* balance(rb::Node<T>* node);
        size_t getHeight(rb::Node<T>* node) const;
        inline void updateHeight(rb::Node<T>* node) { node->height = 1 + std::max(this->getHeight(node->left), this->getHeight(node->right)); }
        inline int balanceFactor(rb::Node<T>* node) { return static_cast<int>(this->getHeight(node->left)) - static_cast<int>(this->getHeight(node->right)); }
        rb::Node<T>* rotateLeft(rb::Node<T>* node);
        rb::Node<T>* rotateRight(rb::Node<T>* node);
        rb::Node<T>* root;
};

template<typename T>
void rb::RedBlackTree<T>::insert(const T& data) {
    this->root = this->insert(this->root, data);
}

template<typename T>
T& rb::RedBlackTree<T>::search(const T& data) {
    rb::Node<T>* searchedNode = this->searchNode(data);
    if (searchedNode == nullptr)
        throw NotFoundException("Item not found when searching");
    return searchedNode->data;
}

template<typename T>
void rb::RedBlackTree<T>::remove(const T& data) {
    rb::Node<T>* removedNode = this->searchNode(data);
    if (removedNode == nullptr)
        throw NotFoundException("Item not found when removing");
    else {
        rb::Node<T>* parent = removedNode->parent;
        if (removedNode->left == nullptr)
            this->transplant(removedNode, removedNode->right);
        else if (removedNode->right == nullptr)
            this->transplant(removedNode, removedNode->left);
        else {
            rb::Node<T>* successor = this->min(removedNode->right);
            if (successor->parent != removedNode) {
                this->transplant(successor, successor->right);
                successor->right = removedNode->right;
                successor->right->parent = successor;
            }
            this->transplant(removedNode, successor);
            successor->left = removedNode->left;
            successor->left->parent = successor;
        }
        delete removedNode;
        while (parent != nullptr) {
            this->balance(parent);
            parent = parent->parent;
        }
    }
}

template<typename T>
T& rb::RedBlackTree<T>::min() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get min from an empty tree");
    else {
        rb::Node<T>* minNode = this->min(this->root);
        return minNode->data;
    }
}

template<typename T>
T& rb::RedBlackTree<T>::max() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get max from an empty tree");
    else {
        rb::Node<T>* maxNode = this->max(this->root);
        return maxNode->data;
    }
}

template<typename T>
void rb::RedBlackTree<T>::destroyRecursive(rb::Node<T>* node) {
    if (node != nullptr) {
        this->destroyRecursive(node->left);
        this->destroyRecursive(node->right);
        delete node;
    }
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::insert(rb::Node<T>* node, const T& data) {
    if (node == nullptr)
        return new rb::Node<T>(data);
    if (data < node->data) {
        node->left = this->insert(node->left, data);
        node->left->parent = node;
    } else {
        node->right = this->insert(node->right, data);
        node->right->parent = node;
    }
    return this->balance(node);
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::searchNode(const T& data) {
    rb::Node<T>* crawlNode = this->root;
    while (crawlNode != nullptr) {
        if (crawlNode->data == data)
            return crawlNode;
        if (data < crawlNode->data)
            crawlNode = crawlNode->left;
        else
            crawlNode = crawlNode->right;
    }
    return crawlNode;
}

template<typename T>
void rb::RedBlackTree<T>::transplant(rb::Node<T>* old, rb::Node<T>* new_) {
    if (old == this->root)
        this->root = new_;
    else if (old == old->parent->left)
        old->parent->left = new_;
    else
        old->parent->right = new_;
    if (new_ != nullptr)
        new_->parent = old->parent;
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::min(rb::Node<T>* subTreeRoot) {
    while (subTreeRoot->left != nullptr)
        subTreeRoot = subTreeRoot->left;
    return subTreeRoot;
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::max(rb::Node<T>* subTreeRoot) {
    while (subTreeRoot->right != nullptr)
        subTreeRoot = subTreeRoot->right;
    return subTreeRoot;
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::balance(rb::Node<T>* node) {
    this->updateHeight(node);
    int bal = this->balanceFactor(node);
    if (bal > 1) {
        if (this->balanceFactor(node->left) >= 0)
            return this->rotateRight(node);
        else {
            node->left = this->rotateLeft(node->left);
            return this->rotateRight(node);
        }
    }
    if (bal < -1) {
        if (this->balanceFactor(node->right) <= 0)
            return this->rotateLeft(node);
        else {
            node->right = this->rotateRight(node->right);
            return this->rotateLeft(node);
        }
    }
    return node;
}

template<typename T>
size_t rb::RedBlackTree<T>::getHeight(rb::Node<T>* node) const {
    if (node == nullptr)
        return 0;
    return node->height;
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::rotateLeft(rb::Node<T>* node) {
    rb::Node<T>* rightChildren = node->right;
    rb::Node<T>* rightChildrenLeft = rightChildren->left;
    node->right = rightChildren->left;
    rightChildren->left = node;
    this->updateHeight(node);
    this->updateHeight(rightChildren);
    this->transplant(node, rightChildren);
    node->parent = rightChildren;
    if (rightChildrenLeft != nullptr)
        rightChildrenLeft->parent = node;
    return rightChildren;
}

template<typename T>
rb::Node<T>* rb::RedBlackTree<T>::rotateRight(rb::Node<T>* node) {
    rb::Node<T>* leftChildren = node->left;
    rb::Node<T>* leftChildrenRight = leftChildren->right;
    node->left = leftChildren->right;
    leftChildren->right = node;
    this->updateHeight(node);
    this->updateHeight(leftChildren);
    this->transplant(node, leftChildren);
    node->parent = leftChildren;
    if (leftChildrenRight != nullptr)
        leftChildrenRight->parent = node;
    return leftChildren;
}

#endif