#ifndef TRIE_HPP_
#define TRIE_HPP_
#include <initializer_list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <queue>

class Trie {
class Node;
public: 
    Trie();
    Trie(std::initializer_list<std::string>);
    Trie(Trie&&) noexcept;
    Trie(const Trie&);
    ~Trie();
public:
    void insert(const std::string&);
    void remove(const std::string&);
    void clear();
    void print() const;
    void printLevelorder() const;
    bool contains(const std::string&) const;
    bool empty() const;
    bool startsWith(const std::string&) const;
    std::size_t size() const;
private:
    bool remove_helper(Node*, const std::string&, int);
    void clear_helper(Node*);
    void print_helper(Node*, const std::string&) const;
    std::size_t size_helper(Node*) const;
    void copy_helper(Node*, Node*);
private:
    class Node {
    public:
        Node();
    public:
        std::unordered_map<char, Node*> m_map;
        bool is_word;
    };
private:
    Node* m_root;
};

#include "Trie.tpp"

#endif //TRIE_HPP_
