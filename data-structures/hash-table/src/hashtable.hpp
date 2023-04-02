#ifndef HADH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <functional>
#include "namespace.hpp"
#include "node.hpp"

template<typename K, typename V, typename H = std::hash<K>>
class HT::HashTable {
    public:
        HashTable();
        ~HashTable();
        size_t hashFunction(K key);
    private:
        size_t capacity;
        size_t numberOfBuckets;
        H _hash;
        HT::Node<K,V>** array;
};

template<typename K, typename V, typename H>
HT::HashTable<K,V,H>::HashTable() {
    this->numberOfBuckets = 0;
    this->capacity = 1;
    this->array = new HT::Node<K,V>*[this->capacity];
    this->array[0] = nullptr;
}

template<typename K, typename V, typename H>
HT::HashTable<K,V,H>::~HashTable() {
    Node<K,V>* temp = nullptr;
    for (size_t i = 0; i < this->capacity; ++i) {
        Node<K,V>* crawlNode = this->array[i];
        while (crawlNode != nullptr) {
            temp = crawlNode;
            crawlNode = crawlNode->next;
            delete temp;
        }
    }
    delete[] this->array;
}

template<typename K, typename V, typename H>
size_t HT::HashTable<K,V,H>::hashFunction(K key) {
    size_t keyHash = this->_hash(key);
    return keyHash % this->capacity;
}

#endif