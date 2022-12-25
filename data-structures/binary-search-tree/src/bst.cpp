#include <string>
#include "namespace.hpp"
#include "bst.hpp"
#include "node.hpp"
#include "exceptions.hpp"

void BST::BinarySearchTree::insert(int data) {
    this->root = this->insert(this->root, data);
}

int BST::BinarySearchTree::search(int data) {
    BST::Node* searchedNode = this->searchNode(data);
    if (searchedNode == nullptr)
        throw NotFoundException("Item " + std::to_string(data) + " not found");
    return searchedNode->data;
}

void BST::BinarySearchTree::remove(int data) {
    BST::Node* removedNode = this->searchNode(data);
    if (removedNode == nullptr)
        throw NotFoundException("Item " + std::to_string(data) + " not found");
    else {
        if (removedNode->left == nullptr)
            this->transplant(removedNode, removedNode->right);
        else if (removedNode->right == nullptr)
            this->transplant(removedNode, removedNode->left);
        else {
            BST::Node* successor = this->min(removedNode->right);
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

int BST::BinarySearchTree::min() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get min from an empty tree");
    else {
        BST::Node* minNode = this->min(this->root);
        return minNode->data;
    }
}

int BST::BinarySearchTree::max() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get max from an empty tree");
    else {
        BST::Node* maxNode = this->max(this->root);
        return maxNode->data;
    }
}

void BST::BinarySearchTree::destroyRecursive(BST::Node* node) {
    if (node != nullptr) {
        this->destroyRecursive(node->left);
        this->destroyRecursive(node->right);
        delete node;
    }
}

BST::Node* BST::BinarySearchTree::insert(BST::Node* node, int data) {
    if (node == nullptr)
        return new BST::Node(data);
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

BST::Node* BST::BinarySearchTree::searchNode(int data) {
    BST::Node* crawlNode = this->root;
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

void BST::BinarySearchTree::transplant(Node* old, Node* new_) {
    if (old == this->root)
        this->root = new_;
    else if (old == old->parent->left)
        old->parent->left = new_;
    else
        old->parent->right = new_;
    if (new_ != nullptr)
        new_->parent = old->parent;
}

BST::Node* BST::BinarySearchTree::min(BST::Node* subTreeRoot) {
    while (subTreeRoot->left != nullptr)
        subTreeRoot = subTreeRoot->left;
    return subTreeRoot;
}

BST::Node* BST::BinarySearchTree::max(BST::Node* subTreeRoot) {
    while (subTreeRoot->right != nullptr)
        subTreeRoot = subTreeRoot->right;
    return subTreeRoot;
}