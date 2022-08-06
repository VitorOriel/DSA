#include <algorithm>
#include <bits/stdc++.h>
#include "heap.h"

Heap::Heap(size_t capacity) {
    this->capacity = this->getAjustedCapacity(capacity);
    this->size = 0;
    this->pData = new int[this->capacity];
}

Heap::Heap(int* array, size_t array_size) {
    this->capacity = this->getAjustedCapacity(array_size);
    for (size_t i = 0; i < array_size; ++i)
        this->insert(array[i]);
    for (size_t i = (this->size-1)/2; i > 0; --i)
        this->heapify(i);
}

void Heap::insert(int data) {
    if (this->size < this->capacity) {
        this->pData[this->size] = data;
        ++this->size;
    }
    throw std::out_of_range("Can't insert due the heap reached the max capacity");
}

void Heap::heapify(size_t i) {
    size_t left = this->left(i);
    size_t right = this->right(i);
    size_t min = i;
    if (left < this->size && this->pData[left] < this->pData[min])
        min = left;
    if (right < this->size && this->pData[right] < this->pData[min])
        min = right;
    if (min != i) {
        std::swap(this->pData[i], this->pData[min]);
        this->heapify(min);
    }
}

size_t Heap::getAjustedCapacity(size_t capacity) {
    size_t powerTwo = 1;
    while (powerTwo < (capacity-1))
        powerTwo <<= 1;
    return (powerTwo+1);
}