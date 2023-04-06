/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef HT_MAP_HPP
#define HT_MAP_HPP

#include <cstddef>
#include <functional>
#include "namespace.hpp"
#include "node.hpp"

template<typename Key_T, typename Value_T, class Hash = std::hash<Key_T>>
class HT::Map {
    public:
        Map() { this->tableConstructor(1); }
        ~Map() { this->tableDestructor(this->array, this->capacity); }
        HT::Node<Key_T,Value_T>* set(const Key_T& key, const Value_T& value);
        Value_T& get(const Key_T& key);
        Value_T& operator[](const Key_T& key);
    private:
        void tableConstructor(size_t capacity);
        void tableDestructor(Node<Key_T,Value_T>** array, size_t capacity);
        float loadFactor() { return static_cast<float>((1 + this->numberOfNodes) / this->capacity); }
        void resize(size_t newCapacity);
        size_t hashFunction(const Key_T& key);
        HT::Node<Key_T,Value_T>* find(const Key_T& key);

        size_t capacity;
        size_t numberOfNodes;
        size_t freeBuckets;
        Hash _hash;
        HT::Node<Key_T,Value_T>** array;
};

template<typename Key_T, typename Value_T, class Hash>
HT::Node<Key_T,Value_T>* HT::Map<Key_T,Value_T,Hash>::set(const Key_T& key, const Value_T& value) {
    while (this->loadFactor() > 0.5f)
        this->resize(this->capacity*2);
    size_t keyIndex = this->hashFunction(key);
    size_t keyHash = this->_hash(key);
    HT::Node<Key_T,Value_T>* crawlNode = this->array[keyIndex];
    HT::Node<Key_T,Value_T>* previousNode = crawlNode;
    while (crawlNode != nullptr && keyHash != this->_hash(crawlNode->key)) {
        previousNode = crawlNode;
        crawlNode = crawlNode->next;
    }
    if (crawlNode == nullptr) {
        HT::Node<Key_T,Value_T>* newNode = new HT::Node<Key_T,Value_T>(key, value);
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

template<typename Key_T, typename Value_T, class Hash>
Value_T& HT::Map<Key_T,Value_T,Hash>::get(const Key_T& key) {
    HT::Node<Key_T,Value_T>* searchedNode = this->find(key);
    if (searchedNode == nullptr)
        throw std::out_of_range("Could not get from key " + std::string(key));
    return searchedNode->value;
}

template<typename Key_T, typename Value_T, class Hash>
Value_T& HT::Map<Key_T,Value_T,Hash>::operator[](const Key_T& key) {
    HT::Node<Key_T,Value_T>* searchedNode = this->find(key);
    if (searchedNode == nullptr)
        searchedNode = this->set(key, Value_T());
    return searchedNode->value;
}

template<typename Key_T, typename Value_T, class Hash>
HT::Node<Key_T,Value_T>* HT::Map<Key_T,Value_T,Hash>::find(const Key_T& key) {
    size_t keyIndex = this->hashFunction(key);
    size_t keyHash = this->_hash(key);
    HT::Node<Key_T,Value_T>* crawlNode = this->array[keyIndex];
    while (crawlNode != nullptr) {
        if (keyHash == this->_hash(crawlNode->key))
            return crawlNode;
        crawlNode = crawlNode->next;
    }
    return crawlNode;
}

template<typename Key_T, typename Value_T, class Hash>
void HT::Map<Key_T,Value_T,Hash>::tableConstructor(size_t capacity) {
    this->numberOfNodes = 0;
    this->capacity = capacity;
    this->freeBuckets = capacity;
    this->array = new HT::Node<Key_T,Value_T>*[this->capacity];
    for (size_t i = 0; i < this->capacity; ++i)
        this->array[i] = nullptr;
}

template<typename Key_T, typename Value_T, class Hash>
void HT::Map<Key_T,Value_T,Hash>::tableDestructor(Node<Key_T,Value_T>** array, size_t capacity) {
    Node<Key_T,Value_T>* temp = nullptr;
    for (size_t i = 0; i < capacity; ++i) {
        Node<Key_T,Value_T>* crawlNode = array[i];
        while (crawlNode != nullptr) {
            temp = crawlNode;
            crawlNode = crawlNode->next;
            delete temp;
        }
    }
    delete[] array;
}

template<typename Key_T, typename Value_T, class Hash>
void HT::Map<Key_T,Value_T,Hash>::resize(size_t newCapacity) {
    size_t oldCapacity = this->capacity;
    Node<Key_T,Value_T>** temp = this->array;
    this->tableConstructor(newCapacity);
    for (size_t i = 0; i < oldCapacity; ++i) {
        Node<Key_T,Value_T>* crawlNode = temp[i];
        while (crawlNode != nullptr) {
            this->set(crawlNode->key, crawlNode->value);
            crawlNode = crawlNode->next;
        }
    }
    this->tableDestructor(temp, oldCapacity);
}

template<typename Key_T, typename Value_T, class Hash>
size_t HT::Map<Key_T,Value_T,Hash>::hashFunction(const Key_T& key) {
    size_t keyHash = this->_hash(key);
    return keyHash % this->capacity;
}

#endif