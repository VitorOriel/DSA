#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
    template<typename U>
    friend class List;

    public:
        Node(T item);
        ~Node();
    protected:
        T data;
        Node* pPrevious;
        Node* pNext;
};

template<typename T>
Node<T>::Node(T item) {
    this->pPrevious = nullptr;
    this->pNext = nullptr;
    this->data = item;
}

template<typename T>
Node<T>::~Node() {
    this->pPrevious = nullptr;
    this->pNext = nullptr;
}

#endif