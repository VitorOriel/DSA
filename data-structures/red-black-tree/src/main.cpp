#include <iostream>
#include "avl.hpp"

using namespace std;

void printTree(rb::AVLTree<int>& tree) {
    for (rb::InorderIterator<int> it = tree.begin(); it.hasNext();)
        cout << it.next() << ' ';
    cout << endl;
}

int main() {
    rb::AVLTree<int> tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    tree.insert(8);
    tree.insert(7);
    tree.insert(0);
    printTree(tree);
    tree.remove(3);
    tree.remove(1);
    tree.remove(4);
    tree.insert(10);
    tree.insert(1);
    tree.insert(3);
    printTree(tree);
    tree.insert(15);
    tree.insert(14);
    tree.insert(13);
    printTree(tree);
    tree.remove(0);
    tree.remove(2);
    tree.remove(3);
    printTree(tree);
    return 0;
}