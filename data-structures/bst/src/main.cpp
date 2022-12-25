#include <iostream>
#include "bst.hpp"
using namespace BST;
using namespace std;

int main() {
    BinaryTree* bst = new BinaryTree();
    bst->insert(2);
    bst->insert(1);
    bst->insert(3);
    for (InorderIterator it = bst->begin(); it.hasNext();)
        cout << it.next() << ' ';
    cout << endl;
    return 0;
}