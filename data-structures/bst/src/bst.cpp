#include <string>
#include "namespace.hpp"
#include "bst.hpp"
#include "node.hpp"
#include "exceptions.hpp"

BST::BinaryTree::BinaryTree() {
    this->root = nullptr;
}

BST::BinaryTree::~BinaryTree() {}

void BST::BinaryTree::insert(int data) {
    this->root = this->insert(this->root, data);
}

int BST::BinaryTree::search(int data) {
    BST::Node* searchedNode = this->searchNode(data);
    if (searchedNode == nullptr)
        throw NotFoundException("Item " + std::to_string(data) + " not found");
    return searchedNode->data;
}

int BST::BinaryTree::min() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get min from an empty tree");
    else {
        BST::Node* minNode = this->min(this->root);
        return minNode->data;
    }
}

int BST::BinaryTree::max() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get max from an empty tree");
    else {
        BST::Node* maxNode = this->max(this->root);
        return maxNode->data;
    }
}

BST::Node* BST::BinaryTree::insert(BST::Node* node, int data) {
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

BST::Node* BST::BinaryTree::searchNode(int data) {
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

BST::Node* BST::BinaryTree::min(BST::Node* subTreeRoot) {
    while (subTreeRoot->left != nullptr)
        subTreeRoot = subTreeRoot->left;
    return subTreeRoot;
}

BST::Node* BST::BinaryTree::max(BST::Node* subTreeRoot) {
    while (subTreeRoot->right != nullptr)
        subTreeRoot = subTreeRoot->right;
    return subTreeRoot;
}