/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#include <bits/stdc++.h>
#include <cstring>
#include <stdexcept>
#include "heap.hpp"

Heap::Heap(size_t capacity) {
    this->capacity = this->getAjustedCapacity(capacity);
    this->size = 0;
    this->data = new int[this->capacity];
}

Heap::Heap(int* array, size_t array_size) {
    this->capacity = this->getAjustedCapacity(array_size);
    this->size = array_size;
    this->data = new int[this->capacity];
    memcpy(this->data, array, array_size*sizeof(int));
    for (size_t i = (this->size-1)/2; i > 0; --i)
        this->leafHeapify(i);
    this->leafHeapify(0);
}

void Heap::insert(int data) {
    if (this->size < this->capacity) {
        this->data[this->size] = data;
        this->rootHeapify(this->size);
        ++this->size;
    } else
        throw std::length_error("Can't insert due the heap reached the max capacity: " + std::to_string(this->capacity));
}

int Heap::removeRoot() {
    if (!this->isEmpty()) {
        int root = this->data[0];
        --this->size;
        std::swap(this->data[0], this->data[this->size]);
        this->leafHeapify(0);
        return root;
    }
    throw std::out_of_range("Can't remove from an empty heap");
}

void Heap::leafHeapify(size_t i) {
    size_t left = this->left(i);
    size_t right = this->right(i);
    size_t min = i;
    if (left < this->size && this->data[left] < this->data[min])
        min = left;
    if (right < this->size && this->data[right] < this->data[min])
        min = right;
    if (min != i) {
        std::swap(this->data[i], this->data[min]);
        this->leafHeapify(min);
    }
}

void Heap::rootHeapify(size_t i) {
    size_t parent = this->parent(i);
    if (this->data[i] < this->data[parent]) {
        std::swap(this->data[i], this->data[parent]);
        this->rootHeapify(parent);
    }
}

size_t Heap::getAjustedCapacity(size_t capacity) {
    size_t powerTwo = 1;
    while (powerTwo < (capacity-1))
        powerTwo <<= 1;
    return (powerTwo+1);
}