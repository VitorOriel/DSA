#ifndef NODE_H
#define NODE_H

class Node {
    friend class BinaryTree;

    public:
        Node(int item);
        ~Node();
    private:
        int data;
        Node* left;
        Node* right;
        Node* parent;
};

Node::Node(int item) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = item;
}

Node::~Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

#endif