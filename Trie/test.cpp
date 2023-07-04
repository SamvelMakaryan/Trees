#include <iostream>
#include "Trie.hpp"

int main() {    
    Trie tree {"C++", "C"};
    tree.insert("hello");
    tree.insert("allo");
    tree.insert("hel");
    std::cout << "> Printing tree" << std::endl;
    tree.print();
    tree.insert("helicopter");
    tree.remove("hel");
    std::cout << "> Printing tree in levelorder" << std::endl;
    tree.printLevelorder();
    std::cout << "> Tree contains 'hel'?  -  " << std::boolalpha << tree.contains("hel") << std::endl;
    std::cout << "> Tree contains 'allo'?  -  " << std::boolalpha << tree.contains("allo") << std::endl;
    std::cout << "> The size of tree is  -  " << tree.size() << std::endl;
    tree.clear();
    std::cout << "> Is tree empty  -  " << std::boolalpha << tree.empty() << std::endl;
    tree.insert("words");
    tree.insert("otherwords");
    Trie tree2(tree);
    std::cout << "> Printing second tree" << std::endl;
    tree2.print();
    std::cout << "> Does second tree have prefix 'word'  -  " << std::boolalpha << tree2.startsWith("word") << std::endl; 
    std::cout << "> Does second tree have prefix 'hello'  -  " << std::boolalpha << tree2.startsWith("hello") << std::endl; 
}
