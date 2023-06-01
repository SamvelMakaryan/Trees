#include <iostream>
#include "AVL.hpp"

int main() {
    AVL<int> ob;
    ob.insert(1);
    ob.insert(2);
    ob.insert(3);
    ob.insert(4);
    ob.insert(5);
    ob.insert(6);
    std::cout << std::endl << "inorder traversal" << std::endl;
    ob.inorder();
    std::cout << std::endl << "preorder traversal" << std::endl;
    ob.preorder();
    std::cout << std::endl << "postorder traversal" << std::endl;
    ob.postorder();
    std::cout << std::endl << "levelorder traversal" << std::endl;
    ob.levelorder();
    ob.levelorder([](int& c) {++c;});
    ob.remove(3);
    std::cout << std::endl << "after changes" << std::endl;
    std::cout << "inorder traversal" << std::endl;
    ob.inorder();
    std::cout << std::endl << "count of nodes - " << ob.size() << std::endl;
    std::cout << "height of tree - " << ob.height() << std::endl;
    std::cout << std::boolalpha << "tree containes 3 - " << ob.contains(3) << std::endl;
    std::cout << std::boolalpha << "tree containes 7 - " << ob.contains(7) << std::endl;
}