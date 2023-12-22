/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <string>

#include "namespace.hpp"
#include "node.hpp"
#include "iterator.hpp"
#include "exceptions.hpp"

template<typename T = avl::BaseData>
class avl::AVLTree {
    public:
        AVLTree() { this->root = nullptr; }
        ~AVLTree() { this->destroyRecursive(this->root); }
        void insert(const T& data);
        int search(const T& data);
        void remove(const T& data);
        int min();
        int max();
        avl::InorderIterator<T> begin() { return avl::InorderIterator<T>(this->root); }
    private:
        void destroyRecursive(avl::Node<T>* node);
        avl::Node<T>* insert(avl::Node<T>* node, const T& data);
        avl::Node<T>* searchNode(const T& data);
        void transplant(avl::Node<T>* old, avl::Node<T>* new_);
        avl::Node<T>* min(avl::Node<T>* subTreeRoot);
        avl::Node<T>* max(avl::Node<T>* subTreeRoot);
        avl::Node<T>* root;
};

template<typename T>
void avl::AVLTree<T>::insert(const T& data) {
    this->root = this->insert(this->root, data);
}

template<typename T>
int avl::AVLTree<T>::search(const T& data) {
    avl::Node<T>* searchedNode = this->searchNode(data);
    if (searchedNode == nullptr)
        throw NotFoundException("Item not found when searching");
    return searchedNode->data;
}

template<typename T>
void avl::AVLTree<T>::remove(const T& data) {
    avl::Node<T>* removedNode = this->searchNode(data);
    if (removedNode == nullptr)
        throw NotFoundException("Item not found when removing");
    else {
        if (removedNode->left == nullptr)
            this->transplant(removedNode, removedNode->right);
        else if (removedNode->right == nullptr)
            this->transplant(removedNode, removedNode->left);
        else {
            avl::Node<T>* successor = this->min(removedNode->right);
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
    }
}

template<typename T>
int avl::AVLTree<T>::min() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get min from an empty tree");
    else {
        avl::Node<T>* minNode = this->min(this->root);
        return minNode->data;
    }
}

template<typename T>
int avl::AVLTree<T>::max() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get max from an empty tree");
    else {
        avl::Node<T>* maxNode = this->max(this->root);
        return maxNode->data;
    }
}

template<typename T>
void avl::AVLTree<T>::destroyRecursive(avl::Node<T>* node) {
    if (node != nullptr) {
        this->destroyRecursive(node->left);
        this->destroyRecursive(node->right);
        delete node;
    }
}

template<typename T>
avl::Node<T>* avl::AVLTree<T>::insert(avl::Node<T>* node, const T& data) {
    if (node == nullptr)
        return new avl::Node<T>(data);
    else {
        if (data < node->data) {
            node->left = this->insert(node->left, data);
            node->left->parent = node;
        } else {
            node->right = this->insert(node->right, data);
            node->right->parent = node;
        }
    }
    return node;
}

template<typename T>
avl::Node<T>* avl::AVLTree<T>::searchNode(const T& data) {
    avl::Node<T>* crawlNode = this->root;
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
void avl::AVLTree<T>::transplant(avl::Node<T>* old, avl::Node<T>* new_) {
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
avl::Node<T>* avl::AVLTree<T>::min(avl::Node<T>* subTreeRoot) {
    while (subTreeRoot->left != nullptr)
        subTreeRoot = subTreeRoot->left;
    return subTreeRoot;
}

template<typename T>
avl::Node<T>* avl::AVLTree<T>::max(avl::Node<T>* subTreeRoot) {
    while (subTreeRoot->right != nullptr)
        subTreeRoot = subTreeRoot->right;
    return subTreeRoot;
}

#endif