#include <iostream>
#include "list.hpp"
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
    cout << "Printing list 1" << endl;
    printList(list);
    List<int> list2 = List<int>(list);
    list2.remove(30);
    list[0] = 0;
    cout << "Printing list 1" << endl;
    printList(list);
    cout << "Printing list 2" << endl;
    printList(list2);
    if (list.contains(0))
        cout << "List contains zero!" << endl;
    return 0;
}