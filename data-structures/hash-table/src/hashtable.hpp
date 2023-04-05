/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <functional>
#include "namespace.hpp"
#include "node.hpp"

template<typename K, typename V, typename H = std::hash<K>>
class HT::HashTable {
    public:
        HashTable() { this->tableConstructor(1); }
        ~HashTable() { this->tableDestructor(this->array, this->capacity); }
        HT::Node<K,V>* set(K key, V value);
        V& get(K key);
        V& operator[](K key);
    private:
        void tableConstructor(size_t capacity);
        void tableDestructor(Node<K,V>** array, size_t capacity);
        float loadFactor() { return static_cast<float>((1 + this->capacity - this->numberOfNodes - this->freeBuckets) / this->capacity); }
        void resize();
        size_t hashFunction(K key);
        HT::Node<K,V>* find(K key);

        size_t capacity;
        size_t numberOfNodes;
        size_t freeBuckets;
        H _hash;
        HT::Node<K,V>** array;
};

template<typename K, typename V, typename H>
HT::Node<K,V>* HT::HashTable<K,V,H>::set(K key, V value) {
    while (this->loadFactor() > 0.5f)
        this->resize();
    size_t keyIndex = this->hashFunction(key);
    size_t keyHash = this->_hash(key);
    HT::Node<K,V>* crawlNode = this->array[keyIndex];
    HT::Node<K,V>* previousNode = crawlNode;
    while (crawlNode != nullptr && keyHash != this->_hash(crawlNode->key)) {
        previousNode = crawlNode;
        crawlNode = crawlNode->next;
    }
    if (crawlNode == nullptr) {
        HT::Node<K,V>* newNode = new HT::Node<K,V>(key, value);
        if (previousNode == nullptr) {
            this->array[keyIndex] = newNode;
            --this->freeBuckets;
        } else
            previousNode->next = newNode;
        ++this->numberOfNodes;
        return newNode;
    } else
        crawlNode->value = value;
    return crawlNode;
}

template<typename K, typename V, typename H>
V& HT::HashTable<K,V,H>::get(K key) {
    HT::Node<K,V>* searchedNode = this->find(key);
    if (searchedNode == nullptr)
        throw std::out_of_range("Could not get from key " + std::string(key));
    return searchedNode->value;
}

template<typename K, typename V, typename H>
V& HT::HashTable<K,V,H>::operator[](K key) {
    HT::Node<K,V>* searchedNode = this->find(key);
    if (searchedNode == nullptr)
        searchedNode = this->set(key, V());
    return searchedNode->value;
}

template<typename K, typename V, typename H>
HT::Node<K,V>* HT::HashTable<K,V,H>::find(K key) {
    size_t keyIndex = this->hashFunction(key);
    size_t keyHash = this->_hash(key);
    HT::Node<K,V>* crawlNode = this->array[keyIndex];
    while (crawlNode != nullptr) {
        if (keyHash == this->_hash(crawlNode->key))
            return crawlNode;
        crawlNode = crawlNode->next;
    }
    return crawlNode;
}

template<typename K, typename V, typename H>
void HT::HashTable<K,V,H>::tableConstructor(size_t capacity) {
    this->numberOfNodes = 0;
    this->capacity = capacity;
    this->freeBuckets = capacity;
    this->array = new HT::Node<K,V>*[this->capacity];
    for (size_t i = 0; i < this->capacity; ++i)
        this->array[i] = nullptr;
}

template<typename K, typename V, typename H>
void HT::HashTable<K,V,H>::tableDestructor(Node<K,V>** array, size_t capacity) {
    Node<K,V>* temp = nullptr;
    for (size_t i = 0; i < capacity; ++i) {
        Node<K,V>* crawlNode = array[i];
        while (crawlNode != nullptr) {
            temp = crawlNode;
            crawlNode = crawlNode->next;
            delete temp;
        }
    }
    delete[] array;
}

template<typename K, typename V, typename H>
void HT::HashTable<K,V,H>::resize() {
    size_t oldCapacity = this->capacity;
    Node<K,V>** temp = this->array;
    this->tableConstructor(this->capacity*2);
    for (size_t i = 0; i < oldCapacity; ++i) {
        Node<K,V>* crawlNode = temp[i];
        while (crawlNode != nullptr) {
            this->set(crawlNode->key, crawlNode->value);
            crawlNode = crawlNode->next;
        }
    }
    this->tableDestructor(temp, oldCapacity);
}

template<typename K, typename V, typename H>
size_t HT::HashTable<K,V,H>::hashFunction(K key) {
    size_t keyHash = this->_hash(key);
    return keyHash % this->capacity;
}

#endif