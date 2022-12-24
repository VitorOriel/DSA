#include <string>
#include "bst.hpp"
#include "node.hpp"
#include "exceptions.hpp"

BinaryTree::BinaryTree() {
    this->root = nullptr;
}

BinaryTree::~BinaryTree() {}

void BinaryTree::insert(int data) {
    this->root = this->insert(this->root, data);
}

int BinaryTree::search(int data) {
    Node* searchedNode = this->searchNode(data);
    if (searchedNode == nullptr)
        throw NotFoundException("Item " + std::to_string(data) + " not found");
    return searchedNode->data;
}

int BinaryTree::min() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get min from an empty tree");
    else {
        Node* minNode = this->min(this->root);
        return minNode->data;
    }
}

int BinaryTree::max() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get max from an empty tree");
    else {
        Node* maxNode = this->max(this->root);
        return maxNode->data;
    }
}

Node* BinaryTree::insert(Node* node, int data) {
    if (node == nullptr)
        return new Node(data);
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

Node* BinaryTree::searchNode(int data) {
    Node* crawlNode = this->root;
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

Node* BinaryTree::min(Node* subTreeRoot) {
    while (subTreeRoot->left != nullptr)
        subTreeRoot = subTreeRoot->left;
    return subTreeRoot;
}

Node* BinaryTree::max(Node* subTreeRoot) {
    while (subTreeRoot->right != nullptr)
        subTreeRoot = subTreeRoot->right;
    return subTreeRoot;
}