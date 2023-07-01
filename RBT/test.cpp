#include <iostream>
#include "RBT.hpp"

int main() {
    RBT<int> tree {5, 5, 4, -1, 8};
    tree.insert(7);
    tree.insert(6); 
    std::cout << std::endl << "Inorder traversal" << std::endl;
    tree.inorder();
    std::cout << std::endl << "Preorder traversal" << std::endl;
    tree.preorder();
    std::cout << std::endl << "Postorder traversal" << std::endl;
    tree.postorder();
    tree.remove(5);
    tree.remove(6);
    std::cout << std::endl << "Levelorder traversal" << std::endl;
    tree.levelorder();
    std::cout << std::endl;
    std::cout << "Contains value 5? " << std::boolalpha << tree.contains(5) << std::endl;
    std::cout << "Contains value 6? " << std::boolalpha << tree.contains(6) << std::endl;
    std::cout << "The size of tree is  -  " << tree.size() << std::endl;
    std::cout << "The height of tree is  -  " << tree.height() << std::endl;
  }