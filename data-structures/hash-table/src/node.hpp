/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef HT_NODE_HPP
#define HT_NODE_HPP

#include "namespace.hpp"

template<typename K, typename V>
class HT::Node {
    template<typename T, typename U, typename H>
    friend class HT::Map;
    public:
        Node(const K& key, const V& value);
        ~Node() { }
        K key;
        V value;
    private:
        Node<K,V>* next;
};

template<typename K, typename V>
HT::Node<K,V>::Node(const K& key, const V& value) {
    this->key = key;
    this->value = value;
    this->next = nullptr;
}

#endif