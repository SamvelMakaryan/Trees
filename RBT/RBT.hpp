#ifndef RBT_HPP_
#define RBT_HPP_
#include <initializer_list>
#include <functional>
#include <iostream>
#include <queue>

enum class Color : bool {
    RED,
    BLACK
};

template <typename T>
class RBT {
class Node;
public:
    RBT();
    RBT(const T&);
    RBT(RBT&&) noexcept;
    RBT(std::initializer_list<T>);
    ~RBT();
public:
    template <typename F = std::function<void(T&)>>
    void inorder(F = [](T& val) {std::cout << val << " ";});
    template <typename F = std::function<void(T&)>>
    void preorder(F = [](T& val) {std::cout << val << " ";});
    template <typename F = std::function<void(T&)>>
    void postorder(F = [](T& val) {std::cout << val << " ";});
    template <typename F = std::function<void(T&)>>
    void levelorder(F = [](T& val) {std::cout << val << " ";});
    void insert(const T&);
    void remove(const T&);
    bool contains(const T&) const;
    std::size_t size() const;
    std::size_t height() const;
private:
    template <typename F>
    void inorder_helper(Node*, F);
    template <typename F>
    void preorder_helper(Node*, F);
    template <typename F>
    void postorder_helper(Node*, F);
    void leftRotate(Node*);
    void rightRotate(Node*);
    void insertFixUp(Node*);
    void removeFixUp(Node*);
    void transplant(Node*, Node*);
    Node* minimum(Node*);
    void clear();
    std::size_t size_helper(Node*) const;
    std::size_t height_helper(Node*) const;
private:
    class Node {
    public:
        Node(const T&);
    public:
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        T val;
    };
private:
    Node* m_root;
    Node* NIL;
};

#include "RBT.tpp"

#endif //RBT_HPP_
