#include <iostream>
#include "heap.h"
using namespace std;

int main() {
    int array[] = {5, 1, 4, 8, 3, 9};
    Heap* heap = new Heap(array, 6);
    heap->insert(2);
    heap->insert(7);
    heap->insert(6);
    while (!heap->isEmpty())
        cout << heap->removeRoot() << ' ';
    cout << endl;
    delete heap;
    return 0;
}