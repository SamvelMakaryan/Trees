#ifndef MAXHEAP_TPP_
#define MAXHEAP_TPP_
#include "MaxHeap.hpp"

template <typename T>
Heap<T>::Heap() = default;


template <typename T>
Heap<T>::~Heap() = default;

template <typename T>
Heap<T>::Heap(const Heap& oth)
: m_heap(oth.m_heap) {}


template <typename T>
Heap<T>::Heap(Heap&& oth) noexcept
: m_heap(std::move(oth.m_heap)) {}

template <typename T>
void Heap<T>::insert(const T& val) {
    m_heap.push_back(val);
    std::size_t index = m_heap.size() - 1;
    std::size_t parent_index = (index - 1) / 2;
    while (index > 0 && m_heap[parent_index] < m_heap[index]) {
        std::swap(m_heap[parent_index], m_heap[index]);
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

template <typename T>
void Heap<T>::remove() {
    if (m_heap.empty()) {
        throw std::logic_error("Tree is empty");
    }
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    heapify(0);
}

template <typename T>
T Heap<T>::max() const {
    if (m_heap.empty()) {
        throw std::logic_error("Tree is empty");
    }
    return m_heap.front();
}

template <typename T>
void Heap<T>::heapify(std::size_t index) {
    std::size_t left = 2 * index + 1; 
    std::size_t right = 2 * index + 2; 
    std::size_t bigest = index;
    if (left < m_heap.size() && m_heap[left] > m_heap[bigest]) {
        bigest = left;
    }
    if (right < m_heap.size() && m_heap[right] > m_heap[bigest]) {
        bigest = right;
    }
    if (bigest != index) {
        std::swap(m_heap[index], m_heap[bigest]);
        heapify(bigest);
    }
}

template <typename T>
void Heap<T>::print() const {
    for (auto& i : m_heap) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template <typename T>
std::size_t Heap<T>::size() const {
    return m_heap.size();
}

template <typename T>
bool Heap<T>::empty() const {
    return m_heap.empty();
}

template <typename T>
void Heap<T>::clear() {
    m_heap.clear();
}

#endif //MAXHEAP_TPP_