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
class rb::RBTree {
    public:
        RBTree() { this->root = nullptr; }
        ~RBTree() { this->destroyRecursive(this->root); }
        void insert(const T& data);
        T search(const T& data);
        void remove(const T& data);
        T min();
        T max();
        rb::InorderIterator<T> begin() { return rb::InorderIterator<T>(this->root); }
    private:
        void destroyRecursive(rb::Node<T>* node);
        void insert(rb::Node<T>*& root, rb::Node<T>* parent, const T& data);
        rb::Node<T>* searchNode(const T& data);
        void transplant(rb::Node<T>* old, rb::Node<T>* new_);
        rb::Node<T>* min(rb::Node<T>* subTreeRoot);
        rb::Node<T>* max(rb::Node<T>* subTreeRoot);
        void insertFixup(rb::Node<T>* node);
        rb::Node<T>* insertFixupForRightUncle(rb::Node<T>* node);
        rb::Node<T>* insertFixupForLeftUncle(rb::Node<T>* node);
        void removeFixup(rb::Node<T>* node);
        rb::Node<T>* removeFixupForRightBrother(rb::Node<T>* node);
        rb::Node<T>* removeFixupForLeftBrother(rb::Node<T>* node);
        void rotateLeft(rb::Node<T>* node);
        void rotateRight(rb::Node<T>* node);
        rb::Node<T>* root;
};

template<typename T>
void rb::RBTree<T>::insert(const T& data) {
    this->insert(this->root, nullptr, data);
}

template<typename T>
T rb::RBTree<T>::search(const T& data) {
    rb::Node<T>* searchedNode = this->searchNode(data);
    if (searchedNode == nullptr)
        throw NotFoundException("Item not found when searching");
    return searchedNode->data;
}

template<typename T>
void rb::RBTree<T>::remove(const T& data) {
    rb::Node<T>* removedNode = this->searchNode(data);
    if (removedNode == nullptr)
        throw NotFoundException("Item not found when removing");
    else {
        rb::Color fixColor = removedNode->color;
        rb::Node<T>* fixWhere;
        if (removedNode->left == nullptr) {
            fixWhere = removedNode->right;
            this->transplant(removedNode, removedNode->right);
        } else if (removedNode->right == nullptr) {
            fixWhere = removedNode->left;
            this->transplant(removedNode, removedNode->left);
        } else {
            rb::Node<T>* successor = this->min(removedNode->right);
            fixColor = successor->color;
            fixWhere = successor->right;
            if (successor->parent != removedNode) {
                this->transplant(successor, successor->right);
                successor->right = removedNode->right;
                successor->right->parent = successor;
            }
            this->transplant(removedNode, successor);
            successor->left = removedNode->left;
            successor->left->parent = successor;
            successor->color = removedNode->color;
        }
        delete removedNode;
        if (fixColor == rb::BLACK && fixWhere != nullptr)
            this->removeFixup(fixWhere);
    }
}

template<typename T>
T rb::RBTree<T>::min() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get min from an empty tree");
    else {
        rb::Node<T>* minNode = this->min(this->root);
        return minNode->data;
    }
}

template<typename T>
T rb::RBTree<T>::max() {
    if (this->root == nullptr)
        throw EmptyTreeException("Can't get max from an empty tree");
    else {
        rb::Node<T>* maxNode = this->max(this->root);
        return maxNode->data;
    }
}

template<typename T>
void rb::RBTree<T>::destroyRecursive(rb::Node<T>* node) {
    if (node != nullptr) {
        this->destroyRecursive(node->left);
        this->destroyRecursive(node->right);
        delete node;
    }
}

template<typename T>
void rb::RBTree<T>::insert(rb::Node<T>*& root, rb::Node<T>* parent, const T& data) {
    if (root == nullptr) {
        root = new rb::Node<T>(data);
        root->parent = parent;
        this->insertFixup(root);
    } else if (data < root->data) {
        this->insert(root->left, root, data);
    } else {
        this->insert(root->right, root, data);
    }
}

template<typename T>
rb::Node<T>* rb::RBTree<T>::searchNode(const T& data) {
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
void rb::RBTree<T>::transplant(rb::Node<T>* old, rb::Node<T>* new_) {
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
rb::Node<T>* rb::RBTree<T>::min(rb::Node<T>* subTreeRoot) {
    while (subTreeRoot->left != nullptr)
        subTreeRoot = subTreeRoot->left;
    return subTreeRoot;
}

template<typename T>
rb::Node<T>* rb::RBTree<T>::max(rb::Node<T>* subTreeRoot) {
    while (subTreeRoot->right != nullptr)
        subTreeRoot = subTreeRoot->right;
    return subTreeRoot;
}

template<typename T>
void rb::RBTree<T>::insertFixup(rb::Node<T>* node) {
    while (node->parent != nullptr && node->parent->color == rb::RED) {
        if (node->parent == node->parent->parent->left) {
            node = this->insertFixupForRightUncle(node);
        } else {
            node = this->insertFixupForLeftUncle(node);
        }
    }
    this->root->color = rb::BLACK;
}

template<typename T>
rb::Node<T>* rb::RBTree<T>::insertFixupForRightUncle(rb::Node<T>* node) {
    rb::Node<T>* rightUncle = node->parent->parent->right;
    if (rightUncle != nullptr && rightUncle->color == rb::RED) {
        node->parent->color = rb::BLACK;
        rightUncle->color = rb::BLACK;
        node->parent->parent->color = rb::RED;
        node = node->parent->parent;
    } else {
        if (node == node->parent->right) {
            node = node->parent;
            this->rotateLeft(node);
        }
        node->parent->color = rb::BLACK;
        node->parent->parent->color = rb::RED;
        this->rotateRight(node->parent->parent);
    }
    return node;
}

template<typename T>
rb::Node<T>* rb::RBTree<T>::insertFixupForLeftUncle(rb::Node<T>* node) {
    rb::Node<T>* leftUncle = node->parent->parent->left;
    if (leftUncle != nullptr && leftUncle->color == rb::RED) {
        node->parent->color = rb::BLACK;
        leftUncle->color = rb::BLACK;
        node->parent->parent->color = rb::RED;
        node = node->parent->parent;
    } else {
        if (node == node->parent->left) {
            node = node->parent;
            this->rotateRight(node);
        }
        node->parent->color = rb::BLACK;
        node->parent->parent->color = rb::RED;
        this->rotateLeft(node->parent->parent);
    }
    return node;
}

template<typename T>
void rb::RBTree<T>::removeFixup(rb::Node<T>* node) {
    while (node != this->root && node->color == rb::BLACK) {
        if (node == node->parent->left) {
            node = this->removeFixupForRightBrother(node);
        } else {
            node = this->removeFixupForLeftBrother(node);
        }
    }
    node->color = rb::BLACK;
}

template<typename T>
rb::Node<T>* rb::RBTree<T>::removeFixupForRightBrother(rb::Node<T>* node) {
    rb::Node<T>* rightBrother = node->parent->right;
    if (rightBrother != nullptr && rightBrother->color == rb::RED) {
        rightBrother->color = rb::BLACK;
        node->parent->color = rb::RED;
        this->rotateLeft(node->parent);
        rightBrother = node->parent->right;
    }
    if ((rightBrother->left == nullptr || rightBrother->left->color == rb::BLACK) &&
        (rightBrother->right == nullptr || rightBrother->right->color == rb::BLACK)) {
        rightBrother->color = rb::RED;
        node = node->parent;
    } else {
        if (rightBrother->right == nullptr || rightBrother->right->color == rb::BLACK) {
            if (rightBrother->left != nullptr) {
                rightBrother->left->color = rb::BLACK;
            }
            rightBrother->color = rb::RED;
            this->rotateRight(rightBrother);
            rightBrother = node->parent->right;
        }
        rightBrother->color = node->parent->color;
        node->parent->color = rb::BLACK;
        if (rightBrother->right != nullptr) {
            rightBrother->right->color = rb::BLACK;
        }
        this->rotateLeft(node->parent);
        node = this->root;
    }
    return node;
}

template<typename T>
rb::Node<T>* rb::RBTree<T>::removeFixupForLeftBrother(rb::Node<T>* node) {
    rb::Node<T>* leftBrother = node->parent->left;
    if (leftBrother != nullptr && leftBrother->color == rb::RED) {
        leftBrother->color = rb::BLACK;
        node->parent->color = rb::RED;
        this->rotateRight(node->parent);
        leftBrother = node->parent->left;
    }
    if ((leftBrother->right == nullptr || leftBrother->right->color == rb::BLACK) &&
        (leftBrother->left == nullptr || leftBrother->left->color == rb::BLACK)) {
        leftBrother->color = rb::RED;
        node = node->parent;
    } else {
        if (leftBrother->left == nullptr || leftBrother->left->color == rb::BLACK) {
            if (leftBrother->right != nullptr) {
                leftBrother->right->color = rb::BLACK;
            }
            leftBrother->color = rb::RED;
            this->rotateLeft(leftBrother);
            leftBrother = node->parent->left;
        }
        leftBrother->color = node->parent->color;
        node->parent->color = rb::BLACK;
        if (leftBrother->left != nullptr) {
            leftBrother->left->color = rb::BLACK;
        }
        this->rotateRight(node->parent);
        node = this->root;
    }
    return node;
}

template<typename T>
void rb::RBTree<T>::rotateLeft(rb::Node<T>* node) {
    rb::Node<T>* rightChildren = node->right;
    node->right = rightChildren->left;
    if (rightChildren->left != nullptr)
        rightChildren->left->parent = node;
    rightChildren->left = node;
    this->transplant(node, rightChildren);
    node->parent = rightChildren;
}

template<typename T>
void rb::RBTree<T>::rotateRight(rb::Node<T>* node) {
    rb::Node<T>* leftChildren = node->left;
    node->left = leftChildren->right;
    if (leftChildren->right != nullptr)
        leftChildren->right->parent = node;
    leftChildren->right = node;
    this->transplant(node, leftChildren);
    node->parent = leftChildren;
}

#endif