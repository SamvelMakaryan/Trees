#ifndef AVL_HPP_
#define AVL_HPP_
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <queue>

template <typename T>
class AVL {
class Node;
public:
    AVL();
    AVL(const T&);
    AVL(const AVL&);
    AVL(AVL&&) noexcept;
    AVL(std::initializer_list<T>);
    ~AVL();
public:
    void insert(const T&);
    void remove(const T&);
    template<typename F = std::function<void(T&)>>
    void inorder(F = [](const T& val) {std::cout << val << " ";});
    template<typename F = std::function<void(T&)>>
    void preorder(F = [](const T& val){std::cout << val << " ";});
    template<typename F = std::function<void(T&)>>
    void postorder(F = [](const T& val){std::cout << val << " ";});
    template<typename F = std::function<void(T&)>>
    void levelorder(F = [](const T& val){std::cout << val << " ";});
    long height() const;
    long size() const;
    void clear();
    bool contains(const T&) const;
private:
    long get_balance_factor(Node*) const;
    long get_height(Node*) const;
    Node* insert_helper(Node*, const T&);
    Node* balance(Node*, const T&);
    void update_height(Node*);
    Node* rotate_left(Node*);
    Node* rotate_right(Node*);
    template <typename F>
    void inorder_helper(Node*, F);
    template <typename F>
    void preorder_helper(Node*, F);
    template <typename F>
    void postorder_helper(Node*, F);
    template <typename F>
    void levelorder_helper(Node*, int, F);
    Node* remove_helper(Node*, const T&);
    void delete_helper(Node*);
    long size_helper(Node*) const;
    Node* find_min_node(Node*);
    Node* copy(Node*);
    bool contains_helper(Node*, const T&) const;
private:
    class Node {
    public:
        Node(const T&);
    public:
        T val;
        Node* left;
        Node* right;
        long height;
    };
private:
    Node* m_root;
};

#include "AVL.tpp"
#endif //AVL_HPP_

