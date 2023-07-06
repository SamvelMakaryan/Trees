#ifndef MINHEAP_HPP_
#define MINHEAP_HPP_
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
    T min() const;
    std::size_t size() const;
    void clear();
private:
    void heapify(std::size_t);
private:
    std::vector<T> m_heap;
};

#include "MinHeap.tpp"

#endif //MINHEAP_HPP_
