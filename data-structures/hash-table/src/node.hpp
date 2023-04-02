#ifndef NODE_HPP
#define NODE_HPP

#include "namespace.hpp"

template<typename K, typename V>
class HT::Node {
    template<typename T, typename U, typename H>
    friend class HT::HashTable;
    public:
        Node();
        ~Node() { }
    private:
        Node<K,V>* next;
        K key;
        V value;
};

template<typename K, typename V>
HT::Node<K,V>::Node() {
    this->next = nullptr;
}

#endif