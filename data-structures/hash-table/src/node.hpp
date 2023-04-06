/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef HT_NODE_HPP
#define HT_NODE_HPP

#include "namespace.hpp"

template<typename Key_T, typename Value_T>
class HT::Node {
    template<typename T, typename U, class Hash>
    friend class HT::Map;
    public:
        Node(const Key_T& key, const Value_T& value);
        ~Node() { }
        Key_T key;
        Value_T value;
    private:
        Node<Key_T,Value_T>* next;
};

template<typename Key_T, typename Value_T>
HT::Node<Key_T,Value_T>::Node(const Key_T& key, const Value_T& value) {
    this->key = key;
    this->value = value;
    this->next = nullptr;
}

#endif