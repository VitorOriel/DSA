#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Node.h"

template<typename T>
class List {
    public:
        List() { this->_List(); }
        List(const List<T>& list);
        ~List();
        void append(T item);
        void remove(T item);
        T& operator[](size_t index);
        T operator[](size_t index) const { return *this[index]; }
        class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
            public:
                Iterator() noexcept : it_pCurrentNode(this->pHead) { }
                Iterator(const Node<T>* pNode) noexcept : it_pCurrentNode(pNode) { }
                Iterator& operator=(T item) {
                    this->it_pCurrentNode->data = item;
                    return *this;
                }
                Iterator& operator++() {
                    if (this->it_pCurrentNode)
                        this->it_pCurrentNode = this->it_pCurrentNode->pNext;
                    return *this;
                }
                Iterator operator++(int) {
                    Iterator iterator = *this;
                    ++*this;
                    return iterator;
                }
                Iterator& operator--() {
                    if (this->it_pCurrentNode)
                        this->it_pCurrentNode = this->it_pCurrentNode->pPrevious;
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
        Iterator begin() noexcept { return Iterator(this->pHead); }
        Iterator cbegin() const noexcept { return Iterator(this->pHead); }
        Iterator rbegin() noexcept { return Iterator(this->pTail); }
        Iterator end() noexcept { return Iterator(nullptr); }
    private:
        void _List(); // Base args constructor
        Node<T>* pHead;
        Node<T>* pTail;
        size_t size;
};

template<typename T>
void List<T>::_List() {
    this->pHead = nullptr;
    this->pTail = nullptr;
    this->size = 0;
}

template<typename T>
List<T>::List(const List<T>& list) {
    this->_List();
    Node<T>* crawlNode = list.pHead;
    while (crawlNode != nullptr) {
        this->append(crawlNode->data);
        crawlNode = crawlNode->pNext;
    }
}

template<typename T>
List<T>::~List() {
    Node<T>* crawlNode = this->pHead;
    while (crawlNode != nullptr) {
        Node<T>* nodeAux = crawlNode;
        crawlNode = crawlNode->pNext;
        delete nodeAux;
    }
}

template<typename T>
void List<T>::append(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (this->pHead == nullptr)
        this->pHead = newNode;
    else {
        newNode->pPrevious = this->pTail;
        this->pTail->pNext = newNode;
    }
    this->pTail = newNode;
    this->size += 1;
}

template<typename T>
void List<T>::remove(T item) {
    Node<T>* foundNode = nullptr;
    Node<T>* crawlNode = this->pHead;
    while (foundNode == nullptr && crawlNode != nullptr) {
        if (item == crawlNode->data)
            foundNode = crawlNode;
        crawlNode = crawlNode->pNext;
    }
    if (foundNode != nullptr) {
        if (foundNode == this->pHead)
            this->pHead = this->pHead->pNext;
        if (foundNode == this->pTail)
            this->pTail = this->pTail->pPrevious;
        if (foundNode->pNext != nullptr)
            foundNode->pNext->pPrevious = foundNode->pPrevious;
        if (foundNode->pPrevious != nullptr)
            foundNode->pPrevious->pNext = foundNode->pNext;
        delete foundNode;
        this->size -= 1;
    }
}

template<typename T>
T& List<T>::operator[](size_t index) {
    if (index < this->size) {
        Node<T>* crawlNode = this->pHead;
        for (size_t i = 0; i < this->size; ++i) {
            if (index == i)
                return crawlNode->data;
            crawlNode = crawlNode->pNext;
        }
    }
    throw std::out_of_range("Index out of range");
}

#endif