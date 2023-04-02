#include <iostream>
#include "hashtable.hpp"

using namespace std;

int main() {
    HT::HashTable<string,int> hashTable = HT::HashTable<string,int>();
    cout << hashTable.hashFunction("batata") << endl;
    return 0;
}