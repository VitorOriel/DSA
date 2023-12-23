#include <iostream>
#include "avl.hpp"

using namespace std;

void printTree(avl::AVLTree<int>& tree) {
    for (avl::InorderIterator<int> it = tree.begin(); it.hasNext();)
        cout << it.next() << ' ';
    cout << endl;
}

int main() {
    avl::AVLTree<int> tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    tree.insert(8);
    tree.insert(7);
    tree.insert(0);
    printTree(tree);
    tree.remove(3);
    printTree(tree);
    return 0;
}