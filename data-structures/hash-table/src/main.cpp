#include <iostream>
#include "hashtable.hpp"

using namespace std;

int main() {
    HT::HashTable<string,int> hashTable = HT::HashTable<string,int>();
    hashTable["test"] = 10;
    cout << hashTable["test"] << endl;
    return 0;
}