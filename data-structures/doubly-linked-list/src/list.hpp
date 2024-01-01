/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"

template<typename T>
class List {
    public:
        List() { this->_List(); }
        List(const List<T>& other);
        ~List();
        void append(const T& data);
        void remove(const T& data);
        inline bool contains(const T& data) { return this->search(data) != nullptr; }
        T& operator[](size_t index);
        class Iterator;
        Iterator begin() noexcept { return Iterator(this->head); }
        Iterator cbegin() const noexcept { return Iterator(this->head); }
        Iterator rbegin() noexcept { return Iterator(this->tail); }
        Iterator end() noexcept { return Iterator(nullptr); }
    private:
        void _List(); // Base args constructor
        Node<T>* search(const T& data);
        Node<T>* head;
        Node<T>* tail;
        size_t size;
};

template<typename T>
class List<T>::Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        Iterator() noexcept : it_pCurrentNode(this->head) { }
        Iterator(const Node<T>* pNode) noexcept : it_pCurrentNode(pNode) { }
        Iterator& operator=(const T& data) {
            this->it_pCurrentNode->data = data;
            return *this;
        }
        Iterator& operator++() {
            if (this->it_pCurrentNode)
                this->it_pCurrentNode = this->it_pCurrentNode->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
        Iterator& operator--() {
            if (this->it_pCurrentNode)
                this->it_pCurrentNode = this->it_pCurrentNode->previous;
            return *this;
        }
        Iterator operator--(int) {
            Iterator iterator = *this;
            --*this;
            return iterator;
        }
        bool operator==(const Iterator& iterator) {
            return this->it_pCurrentNode == iterator.it_pCurrentNode;
        }
        bool operator!=(const Iterator& iterator) {
            return this->it_pCurrentNode != iterator.it_pCurrentNode;
        }
        T operator*() {
            return this->it_pCurrentNode->data;
        }
    private:
        const Node<T>* it_pCurrentNode;
};

template<typename T>
void List<T>::_List() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template<typename T>
List<T>::List(const List<T>& other) {
    this->_List();
    Node<T>* crawlNode = other.head;
    while (crawlNode != nullptr) {
        this->append(crawlNode->data);
        crawlNode = crawlNode->next;
    }
}

template<typename T>
List<T>::~List() {
    Node<T>* crawlNode = this->head;
    while (crawlNode != nullptr) {
        Node<T>* nodeAux = crawlNode;
        crawlNode = crawlNode->next;
        delete nodeAux;
    }
}

template<typename T>
void List<T>::append(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (this->head == nullptr)
        this->head = newNode;
    else {
        newNode->previous = this->tail;
        this->tail->next = newNode;
    }
    this->tail = newNode;
    this->size += 1;
}

template<typename T>
void List<T>::remove(const T& data) {
    Node<T>* searchedNode = this->search(data);
    if (searchedNode != nullptr) {
        if (searchedNode == this->head)
            this->head = this->head->next;
        if (searchedNode == this->tail)
            this->tail = this->tail->previous;
        if (searchedNode->next != nullptr)
            searchedNode->next->previous = searchedNode->previous;
        if (searchedNode->previous != nullptr)
            searchedNode->previous->next = searchedNode->next;
        delete searchedNode;
        this->size -= 1;
    }
}

template<typename T>
T& List<T>::operator[](size_t index) {
    if (index < this->size) {
        Node<T>* crawlNode = this->head;
        for (size_t i = 0; i < this->size; ++i) {
            if (index == i)
                return crawlNode->data;
            crawlNode = crawlNode->next;
        }
    }
    throw std::out_of_range("Index out of range");
}

template<typename T>
Node<T>* List<T>::search(const T& data) {
    Node<T>* crawlNode = this->head;
    while (crawlNode != nullptr) {
        if (data == crawlNode->data)
            return crawlNode;
        crawlNode = crawlNode->next;
    }
    return nullptr;
}

#endif