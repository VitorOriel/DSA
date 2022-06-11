#include <iostream>
#include "List.h"
using namespace std;

int main() {
    List<int>* list = new List<int>();
    list->append(5);
    list->append(10);
    list->print();
    delete list;
    return 0;
}