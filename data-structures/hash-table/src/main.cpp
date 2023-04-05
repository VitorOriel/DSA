#include <iostream>
#include "hashtable.hpp"

using namespace std;

int main() {
    HT::HashTable<string,int> hashTable = HT::HashTable<string,int>();
    hashTable["test"] = 15;
    hashTable["test2"] = hashTable["test"];
    cout << hashTable["test2"] << endl;
    return 0;
}