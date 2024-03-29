#include <iostream>
#include "bst.hpp"

using namespace std;

void printTree(BST::BinarySearchTree* tree) {
    for (BST::InorderIterator it = tree->begin(); it.hasNext();)
        cout << it.next() << ' ';
    cout << endl;
}

int main() {
    BST::BinarySearchTree* bst = new BST::BinarySearchTree();
    bst->insert(3);
    bst->insert(1);
    bst->insert(2);
    bst->insert(4);
    bst->insert(8);
    bst->insert(7);
    bst->insert(0);
    printTree(bst);
    bst->remove(3);
    printTree(bst);
    delete bst;
    return 0;
}