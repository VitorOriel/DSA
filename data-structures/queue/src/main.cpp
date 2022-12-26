#include <iostream>
#include "queue.hpp"
using namespace std;

void printQueue(Queue<int>* queue) {
    while (!queue->isEmpty())
        cout << queue->dequeue() << ' ';
    cout << endl;
}

int main() {
    Queue<int>* queue = new Queue<int>();
    queue->enqueue(1);
    queue->enqueue(2);
    queue->enqueue(3);
    queue->enqueue(4);
    Queue<int>* queue2 = new Queue<int>(*queue);
    queue2->enqueue(5);
    queue2->dequeue();
    printQueue(queue);
    printQueue(queue2);
    delete queue2;
    delete queue;
    return 0;
}