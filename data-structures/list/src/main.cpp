#include <iostream>
#include "List.h"
using namespace std;

void printList(List<int>* list) {
    for (List<int>::Iterator it = list->begin(); it != list->end(); ++it)
        cout << *it << ' ';
    cout << endl;
    for (List<int>::Iterator it = list->rbegin(); it != list->end(); --it)
        cout << *it << ' ';
    cout << endl;
}

int main() {
    List<int>* list = new List<int>();
    list->append(10);
    list->append(20);
    list->append(30);
    printList(list);
    list->remove(30);
    printList(list);
    delete list;
    return 0;
}