/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef HT_NODE_HPP
#define HT_NODE_HPP

#include "namespace.hpp"

template<typename Key_T, typename Value_T>
class ht::Node {
    template<typename K, typename V, class Hash>
    friend class ht::Map;
    public:
        Node(const Key_T& key, const Value_T& value);
        ~Node() { }
        Key_T key;
        Value_T value;
    private:
        Node<Key_T,Value_T>* next;
};

template<typename Key_T, typename Value_T>
ht::Node<Key_T,Value_T>::Node(const Key_T& key, const Value_T& value) {
    this->key = key;
    this->value = value;
    this->next = nullptr;
}

#endif