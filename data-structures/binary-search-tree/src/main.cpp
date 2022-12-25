#include <iostream>
#include "bst.hpp"
using namespace BST;
using namespace std;

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    bst->insert(2);
    bst->insert(1);
    bst->insert(3);
    for (InorderIterator it = bst->begin(); it.hasNext();)
        cout << it.next() << ' ';
    cout << endl;
    delete bst;
    return 0;
}