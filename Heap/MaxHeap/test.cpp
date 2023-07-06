#include <iostream>
#include "MaxHeap.hpp"

int main() {
    Heap<int> heap;
    heap.insert(5);
    heap.insert(-2);
    heap.insert(1);
    heap.insert(4);
    heap.insert(-3);
    std::cout << "> Printing heap" << std::endl;
    heap.print();
    heap.remove();
    try {
        std::cout << "> The maximum value of heap  -  " << heap.max() << std::endl;
    } catch (const std::logic_error& ex) {
        std::cerr << ex.what() << std::endl;
    }
    heap.insert(-7);
    heap.insert(-7);
    heap.remove();
    std::cout << "> Printing heap" << std::endl;
    heap.print();
    std::cout << "> Is heap empty  -  " << std::boolalpha << heap.empty() << std::endl;
    std::cout << "> Size of heap  -  " << heap.size() << std::endl;
    Heap heap2(heap);
    std::cout << "> Printing second heap" << std::endl;
    heap2.print();
    heap2.clear();
    try {
        std::cout << "> The maximum value of second heap  -  " << heap2.max() << std::endl;
    } catch (const std::logic_error& ex) {
        std::cerr << ex.what() << std::endl;
    }
}