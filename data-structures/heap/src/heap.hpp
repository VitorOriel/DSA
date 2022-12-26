/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include <cstddef>

class Heap {
    public:
        Heap(size_t capacity);
        Heap(int* array, size_t array_size);
        ~Heap() { delete[] this->pData; }
        inline bool isEmpty() { return this->size == 0; }
        void insert(int data);
        int removeRoot();
    private:
        size_t getAjustedCapacity(size_t capacity);
        void leafHeapify(size_t i);
        void rootHeapify(size_t i);
        inline const size_t left(size_t i) { return (i*2 + 1); }
        inline const size_t right(size_t i) { return (i*2 + 2); }
        inline const size_t parent(size_t i) { return ((i-1)/2); }
        int* pData;
        size_t size;
        size_t capacity;
};

#endif