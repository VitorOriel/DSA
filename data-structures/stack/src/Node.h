#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
    template<typename U>
    friend class Stack;

    public:
        Node(T item);
        ~Node();
    private:
        T data;
        Node* pNext;
};

template<typename T>
Node<T>::Node(T item) {
    this->pNext = nullptr;
    this->data = item;
}

template<typename T>
Node<T>::~Node() {
    this->pNext = nullptr;
}

#endif