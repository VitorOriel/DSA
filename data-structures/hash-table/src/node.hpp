/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef NODE_HPP
#define NODE_HPP

#include "namespace.hpp"

template<typename K, typename V>
class HT::Node {
    template<typename T, typename U, typename H>
    friend class HT::HashTable;
    public:
        Node(K key, V value);
        ~Node() { }
        K key;
        V value;
    private:
        Node<K,V>* next;
};

template<typename K, typename V>
HT::Node<K,V>::Node(K key, V value) {
    this->key = key;
    this->value = value;
    this->next = nullptr;
}

#endif