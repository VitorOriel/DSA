#include <iostream>
#include "hashtable.hpp"

using namespace std;

int main() {
    HT::HashTable<string,int> hashTable;
    hashTable["test"] = 15;
    hashTable["test2"] = hashTable["test"];
    cout << hashTable["test2"] << endl;
    try {
        cout << hashTable.get("test3") << endl;
    } catch (std::out_of_range& e) {
        cout << e.what() << endl;
    }
    return 0;
}