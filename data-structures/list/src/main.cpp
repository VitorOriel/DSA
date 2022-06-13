#include <iostream>
#include "List.h"
using namespace std;

void printList(List<int>& list) {
    for (int item : list)
        cout << item << ' ';
    cout << endl;
    for (List<int>::Iterator it = list.rbegin(); it != list.end(); --it)
        cout << *it << ' ';
    cout << endl;
}

int main() {
    List<int> list = List<int>();
    list.append(10);
    list.append(20);
    list.append(30);
    printList(list);
    list.remove(30);
    printList(list);
    return 0;
}