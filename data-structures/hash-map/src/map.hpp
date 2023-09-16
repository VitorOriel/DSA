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
        Value_T erase(const Key_T& key);
        Value_T& operator[](const Key_T& key);
        class Iterator;
        Iterator begin() noexcept { return Iterator(this->array); }
        Iterator cbegin() const noexcept { return Iterator(this->array); }
        Iterator end() noexcept { return Iterator(this->numberOfNodes); }
    private:
        void tableConstructor(size_t capacity);
        void tableDestructor(Node<Key_T,Value_T>** array, size_t capacity);
        float loadFactor() { return static_cast<float>((1 + this->numberOfNodes) / this->capacity); }
        void resize(size_t newCapacity);
        size_t hashFunction(const Key_T& key) { return this->hash(key) % this->capacity; }
        HT::Node<Key_T,Value_T>* find(const Key_T& key);
        std::pair<HT::Node<Key_T,Value_T>*,HT::Node<Key_T,Value_T>*> findWithPrevious(const Key_T& key);

        size_t capacity;
        size_t numberOfNodes;
        size_t freeBuckets;
        Hash hash;
        HT::Node<Key_T,Value_T>** array;
};

template<typename Key_T, typename Value_T, class Hash>
HT::Node<Key_T,Value_T>* HT::Map<Key_T,Value_T,Hash>::set(const Key_T& key, const Value_T& value) {
    if (this->loadFactor() > 0.5f)
        this->resize(this->capacity*2);
    std::pair<HT::Node<Key_T,Value_T>*,HT::Node<Key_T,Value_T>*> nodesPair = this->findWithPrevious(key);
    if (nodesPair.second == nullptr) {
        HT::Node<Key_T,Value_T>* newNode = new HT::Node<Key_T,Value_T>(key, value);
        if (nodesPair.first == nullptr) {
            this->array[this->hashFunction(key)] = newNode;
            --this->freeBuckets;
        } else
            nodesPair.first->next = newNode;
        ++this->numberOfNodes;
        return newNode;
    } else
        nodesPair.second->value = value;
    return nodesPair.second;
}

template<typename Key_T, typename Value_T, class Hash>
Value_T& HT::Map<Key_T,Value_T,Hash>::get(const Key_T& key) {
    HT::Node<Key_T,Value_T>* searchedNode = this->find(key);
    if (searchedNode == nullptr)
        throw std::out_of_range("HT::Map::get | could not get from key");
    return searchedNode->value;
}

template<typename Key_T, typename Value_T, class Hash>
Value_T HT::Map<Key_T,Value_T,Hash>::erase(const Key_T& key) {
    std::pair<HT::Node<Key_T,Value_T>*,HT::Node<Key_T,Value_T>*> nodesPair = this->findWithPrevious(key);
    if (nodesPair.second == nullptr)
        throw std::out_of_range("HT::Map::erase | could not erase from key");
    HT::Node<Key_T,Value_T>* temp = nodesPair.second;
    Value_T returnedValue = temp->value;
    if (nodesPair.first == nullptr) {
        HT::Node<Key_T,Value_T>* nextNode = nodesPair.second->next;
        this->array[this->hashFunction(key)] = nextNode;
        if (nextNode == nullptr)
            ++this->freeBuckets;
    } else
        nodesPair.first->next = nodesPair.second->next;
    --this->numberOfNodes;
    delete temp;
    if (this->loadFactor() < 0.25f)
        this->resize(this->capacity/2);
    return returnedValue;
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
    size_t keyHash = this->hash(key);
    HT::Node<Key_T,Value_T>* crawlNode = this->array[this->hashFunction(key)];
    while (crawlNode != nullptr) {
        if (keyHash == this->hash(crawlNode->key))
            return crawlNode;
        crawlNode = crawlNode->next;
    }
    return crawlNode;
}

template<typename Key_T, typename Value_T, class Hash>
std::pair<HT::Node<Key_T,Value_T>*,HT::Node<Key_T,Value_T>*> HT::Map<Key_T,Value_T,Hash>::findWithPrevious(const Key_T& key) {
    size_t keyHash = this->hash(key);
    HT::Node<Key_T,Value_T>* crawlNode = this->array[this->hashFunction(key)];
    HT::Node<Key_T,Value_T>* previousNode = nullptr;
    while (crawlNode != nullptr) {
        if (keyHash == this->hash(crawlNode->key))
            return std::pair<HT::Node<Key_T,Value_T>*,HT::Node<Key_T,Value_T>*>(previousNode, crawlNode);
        previousNode = crawlNode;
        crawlNode = crawlNode->next;
    }
    return std::pair<HT::Node<Key_T,Value_T>*,HT::Node<Key_T,Value_T>*>(previousNode, crawlNode);
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
class HT::Map<Key_T,Value_T,Hash>::Iterator : public std::iterator<std::forward_iterator_tag, HT::Node<Key_T,Value_T>*> {
    public:
        // HT::Map::begin()
        Iterator(HT::Node<Key_T,Value_T>** mapArray);
        // HT::Map::end()
        Iterator(size_t currentNodeIndex);
        Iterator& operator++() { this->moveToNextNode(); ++this->currentNodeIndex; return *this; }
        Iterator operator++(int) { Iterator iterator = *this; ++*this; return iterator; }
        bool operator==(const Iterator& other) { return this->currentNodeIndex == other.currentNodeIndex; }
        bool operator!=(const Iterator& other) { return this->currentNodeIndex != other.currentNodeIndex; }
        HT::Node<Key_T,Value_T>* operator*() const { return this->currentNode; }
        HT::Node<Key_T,Value_T>* operator->() const { return this->currentNode; }
    private:
        void moveToNextNode();

        HT::Node<Key_T,Value_T>** mapArray;
        HT::Node<Key_T,Value_T>* currentNode;
        size_t currentMapIndex;
        size_t currentNodeIndex;
};

template<typename Key_T, typename Value_T, class Hash>
HT::Map<Key_T,Value_T,Hash>::Iterator::Iterator(HT::Node<Key_T,Value_T>** mapArray) {
    this->mapArray = mapArray;
    this->currentMapIndex = 0;
    this->currentNodeIndex = 0;
    this->currentNode = this->mapArray[0];
    if (this->currentNode == nullptr)
        this->moveToNextNode();
}

template<typename Key_T, typename Value_T, class Hash>
HT::Map<Key_T,Value_T,Hash>::Iterator::Iterator(size_t currentNodeIndex) {
    this->mapArray = nullptr;
    this->currentMapIndex = 0;
    this->currentNodeIndex = currentNodeIndex;
    this->currentNode = nullptr;
}

template<typename Key_T, typename Value_T, class Hash>
void HT::Map<Key_T,Value_T,Hash>::Iterator::moveToNextNode() {
    if (this->currentNode != nullptr)
        this->currentNode = this->currentNode->next;
    while (this->currentNode == nullptr)
        this->currentNode = this->mapArray[++this->currentMapIndex];
}

#endif