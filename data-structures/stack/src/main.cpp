#include <iostream>
#include "stack.hpp"
using namespace std;

void printStack(Stack<int>* stack) {
    while (!stack->isEmpty())
        cout << stack->pop() << ' ';
    cout << endl;
}

int main() {
    Stack<int>* stack = new Stack<int>();
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(4);
    Stack<int>* stack2 = new Stack<int>(*stack);
    stack2->pop();
    stack2->push(5);
    printStack(stack);
    printStack(stack2);
    delete stack2;
    delete stack;
    return 0;
}