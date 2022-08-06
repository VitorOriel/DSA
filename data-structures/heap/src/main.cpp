#include <iostream>
#include "heap.h"
using namespace std;

int main() {
    int array[5] = {5, 1, 4, 2, 3};
    Heap* heap = new Heap(array, 5);
    while (!heap->isEmpty())
        cout << heap->removeRoot() << ' ';
    cout << endl;
    delete heap;
    return 0;
}