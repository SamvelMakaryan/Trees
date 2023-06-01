#ifndef AVL_TPP_
#define AVL_TPP_
#include "AVL.hpp"

template <typename T>
AVL<T>::Node::Node(const T& val) 
    : val(val),
      left(nullptr),
      right(nullptr),
      height(1) {}

template <typename T>
AVL<T>::AVL()
    : m_root(nullptr) {}

template <typename T>
AVL<T>::AVL(const T& val)
    : m_root(new Node(val)) {}

template <typename T>
AVL<T>::AVL(const AVL& oth)
    : m_root(copy(oth.root)) {} 

template <typename T>
AVL<T>::AVL(AVL&& oth) noexcept
    : m_root(oth.m_root)
    {
        oth.m_root = nullptr;
    }

template <typename T>
AVL<T>::AVL(std::initializer_list<T> init) {
    for (auto& i : init) {
        insert(i);
    }
}

template <typename T>
AVL<T>::~AVL() {
    delete_helper(m_root);
    m_root = nullptr;
}

template <typename T>
long AVL<T>::get_balance_factor(Node* node) const {
    if (!node) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

template <typename T>
void AVL<T>::insert(const T& val) {
    m_root = insert_helper(m_root, val);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insert_helper(Node* node, const T& val) {
    if (!node) {
        return new Node(val);
    }
    if (val > node->val) {
        node->right = insert_helper(node->right, val);
    }
    else if (val < node->val) {
        node->left = insert_helper(node->left, val);
    }
    else {
        return node;
    }   
    return balance(node, val);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::balance(Node* node, const T& val) {
    update_height(node);
    long balance_factor = get_balance_factor(node);
    if (balance_factor > 1 && val < node->left->val) {
        return rotate_right(node);
    }
    if (balance_factor < -1 && val > node->right->val) {
        return rotate_left(node);
    }
    if (balance_factor > 1 && val > node->left->val) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance_factor < -1 && val < node->right->val) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

template <typename T>
void AVL<T>::update_height(Node* node) {
    node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}

template <typename T>
long AVL<T>::get_height(Node* node) const {
    if(!node) {
        return 0;
    }
    return node->height;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotate_left(Node* node) {
    Node* new_root = node->right;
    Node* subtree = new_root->left;
    new_root->left = node;
    node->right = subtree;
    update_height(node);
    update_height(new_root);
    return new_root;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotate_right(Node* node) {
    Node* new_root = node->left;
    Node* subtree = new_root->right;
    new_root->right = node;
    node->left = subtree;
    update_height(node);
    update_height(new_root);
    return new_root;
}

template <typename T>
template <typename F>
void AVL<T>::inorder(F visit) {
    inorder_helper(m_root, visit);
}

template <typename T>
template <typename F>
void AVL<T>::preorder(F visit) {
    preorder_helper(m_root, visit);
}

template <typename T>
template <typename F>
void AVL<T>::postorder(F visit) {
    postorder_helper(m_root, visit);
}

template <typename T>
template <typename F>
void AVL<T>::levelorder(F visit) {
    for (long i = 0; i <= m_root->height; ++i) {
        levelorder_helper(m_root, i, visit);
    }
}

template <typename T>
template <typename F>
void AVL<T>::inorder_helper(Node* node, F visit) {
    if (node) {
        inorder_helper(node->left, visit);
        visit(node->val);
        inorder_helper(node->right, visit);
    }
}

template <typename T>
template <typename F>
void AVL<T>::preorder_helper(Node* node, F visit) {
    if (node) {
        visit(node->val);
        preorder_helper(node->left, visit);    
        preorder_helper(node->right, visit);
    }
}

template <typename T>
template <typename F>
void AVL<T>::postorder_helper(Node* node, F visit) {
    if (node) {
        postorder_helper(node->left, visit);
        postorder_helper(node->right, visit);
        visit(node->val);
    }
}

template <typename T>
template <typename F>
void AVL<T>::levelorder_helper(Node* node, int level, F visit) {
    if (!node) {
        return;
    }
    if (level == 1) {
        visit(node->val);
    }
    else if(level > 1) {
        levelorder_helper(node->left, level - 1, visit);
        levelorder_helper(node->right, level - 1, visit);
    }
}

template <typename T>
long AVL<T>::height() const {
    return get_height(m_root);
}

template <typename T>
void AVL<T>::remove(const T& val) {
    m_root = remove_helper(m_root, val);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::remove_helper(Node* node, const T& val) {
    if (!node) {
        return node;
    }
    if (node->val > val) {
        node->left = remove_helper(node->left, val);
    }
    else if(node->val < val) {
        node->right = remove_helper(node->right, val);
    }
    else {
        if (!node->left) {
            Node* tmp = node->right;
            delete node;
            return tmp;
        }
        if (!node->right) {
            Node* tmp = node->left;
            delete node;
            return tmp;
        }
        Node* tmp = find_min_node(node->right);
        node->val = tmp->val;
        node->right = remove_helper(node->right, tmp->val);
    }
    return balance(node, val);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::find_min_node(Node* node) {
    if (!node) {
        return node;
    }
    Node* tmp = node;
    while (tmp->left) {
        tmp = tmp->left;
    }
    return tmp;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::copy(Node* node) {
    if (!node) {
        return node;
    }
    Node* new_node = new Node(node->val);
    new_node->right = copy(new_node->right); 
    new_node->left = copy(new_node->left); 
    return new_node;
}

template <typename T>
void AVL<T>::delete_helper(Node* node) {
    if (!node) {
        return;
    }
    delete_helper(node->left);
    delete_helper(node->right);
    delete node;
}

template <typename T>
void AVL<T>::clear() {
    delete_helper(m_root);
    m_root = nullptr;
}

template <typename T>
long AVL<T>::size() const {
    return size_helper(m_root);
}

template <typename T>
long AVL<T>::size_helper(Node* node) const {
    if (!node) {
        return 0;
    }
    long l = size_helper(node->left);
    long r = size_helper(node->right);
    return l + r + 1;
}

template <typename T>
bool AVL<T>::contains(const T& val) const {
    return contains_helper(m_root, val);
}

template <typename T>
bool AVL<T>::contains_helper(Node* node, const T& val) const {
    if (!node) {
        return false;
    }
    if (val > node->val) {
        return contains_helper(node->right, val);
    }
    else if (val < node->val) {
        return contains_helper(node->left, val);
    }
    else {
        return true;
    }
}

#endif //AVL_TPP_