#ifndef MAXHEAP_HPP_
#define MAXHEAP_HPP_
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <vector>

template <typename T>
class Heap {
public:
    Heap();
    Heap(const Heap&);
    Heap(Heap&&) noexcept;
    ~Heap();
public:
    void insert(const T&);
    void remove();
    void print() const;
    bool empty() const;
    T max() const;
    std::size_t size() const;
    void clear();
private:
    void heapify(std::size_t);
private:
    std::vector<T> m_heap;
};

#include "MaxHeap.tpp"

#endif //MAXHEAP_HPP_
