#ifndef RBT_TPP_
#define RBT_TPP_
#include "RBT.hpp"

template <typename T>
RBT<T>::Node::Node(const T& val) 
  : val(val),
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    color(Color::RED) {}

template <typename T>
RBT<T>::RBT()
  : NIL(new Node(T()))
  {
    m_root = NIL;
    NIL->color = Color::BLACK;
  }

template <typename T>
RBT<T>::RBT(const T& val)
  : m_root(new Node(val)),
    NIL(new Node(T()))
  {
    NIL->color = Color::BLACK;
    m_root->color = Color::BLACK;
  }

template <typename T>
RBT<T>::RBT(RBT&& oth) noexcept
  : m_root(oth.m_root),
    NIL(oth.NIL)
    {
      oth.m_root = nullptr;
      oth.NIL = nullptr;
    }

template <typename T>
RBT<T>::RBT(std::initializer_list<T>init)
  : NIL(new Node(T()))
  {
    NIL->color = Color::BLACK;
    m_root = NIL;
    for (auto& i : init) {
      insert(i);
    }
  }

template <typename T>
RBT<T>::~RBT() {
  clear();
}

template <typename T>
void RBT<T>::leftRotate(Node* node) {
  Node* tmp = node->right;
  node->right = tmp->left;
  if (tmp->left != NIL) {
    tmp->left->parent = node;
  }
  tmp->parent = node->parent;
  if (node->parent == NIL) {
    m_root = tmp;
  } else if (node == node->parent->left) {
    node->parent->left = tmp;
  } else {
    node->parent->right = tmp;
  }
  tmp->left = node;
  node->parent = tmp;
}

template <typename T>
void RBT<T>::rightRotate(Node* node) {
  Node* tmp = node->left;
  node->left = tmp->right;
  if (tmp->right != NIL) {
    tmp->right->parent = node;
  }
  tmp->parent = node->parent;
  if (node->parent == NIL) {
    m_root = tmp;
  } else if (node->parent->left == node) {
    node->parent->left = tmp;
  } else {
    node->parent->right = tmp;
  }
  tmp->right = node;
  node->parent = tmp;
}

template <typename T>
void RBT<T>::insert(const T& val) {
  Node* node = m_root;
  Node* parent = NIL;
  Node* new_node = new Node(val);
  while (node != NIL) {
    parent = node;
    if (val < node->val) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  new_node->parent = parent;
  if (parent == NIL) {
    m_root = new_node;
  } else if (val < parent->val) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
  new_node->left = NIL;
  new_node->right = NIL;
  insertFixUp(new_node);
}

template <typename T>
void RBT<T>::insertFixUp(Node* node) {
  while (node->parent->color == Color::RED) {
    if (node->parent == node->parent->parent->left) {
      Node* uncle = node->parent->parent->right;
      if (uncle->color == Color::RED) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          leftRotate(node);
        }
        node->parent->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        rightRotate(node->parent->parent);
      }
    } else {
      Node* uncle = node->parent->parent->left;
      if (uncle->color == Color::RED) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rightRotate(node);
        }
        node->parent->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        leftRotate(node->parent->parent);
      }
    }
  }
  m_root->color = Color::BLACK;
}

template <typename T>
template <typename F>
void RBT<T>::levelorder(F visit) {
  if (m_root == NIL) {
    return;
  }
  std::queue<Node*> q;
  q.push(m_root);
  while (!q.empty()) {
    Node* tmp = q.front();
    q.pop();
    if (tmp->left != NIL) {
      q.push(tmp->left);
    }
    if (tmp->right != NIL) {
      q.push(tmp->right);
    }
    visit(tmp->val);
  }
}

template <typename T>
template <typename F>
void RBT<T>::inorder(F visit) {
  inorder_helper(m_root, visit);
}

template <typename T>
template <typename F>
void RBT<T>::preorder(F visit) {
  preorder_helper(m_root, visit);
}

template <typename T>
template <typename F>
void RBT<T>::postorder(F visit) {
  postorder_helper(m_root, visit);
}

template <typename T>
template <typename F>
void RBT<T>::inorder_helper(Node* node, F visit) {
  if (node != NIL) {
    inorder_helper(node->left, visit);
    visit(node->val);
    inorder_helper(node->right, visit);
  }
}


template <typename T>
template <typename F>
void RBT<T>::preorder_helper(Node* node, F visit) {
  if (node != NIL) {
    visit(node->val);
    preorder_helper(node->left, visit);
    preorder_helper(node->right, visit);
  }
}

template <typename T>
template <typename F>
void RBT<T>::postorder_helper(Node* node, F visit) {
  if (node != NIL) {
    postorder_helper(node->left, visit);
    postorder_helper(node->right, visit);
    visit(node->val);
  }
}

template <typename T>
void RBT<T>::remove(const T& val) {
  Node* removing_node = m_root;
  while (removing_node != NIL) {
    if (val < removing_node->val) {
      removing_node = removing_node->left;
    } else if (val > removing_node->val) {
      removing_node = removing_node->right;
    } else {
      break;
    }
  }
  if (removing_node == NIL) {
    return;
  }
  Node* tmp = removing_node;
  Color original_color = tmp->color;
  Node* x;
  if (removing_node->left == NIL) {
    x = removing_node->right;
    transplant(removing_node, removing_node->right);
  } else if (removing_node->right == NIL) {
    x = removing_node->left;
    transplant(removing_node, removing_node->left);
  } else {
    tmp = minimum(removing_node->right);
    original_color = tmp->color;
    x = tmp->right;
    if (tmp != removing_node->right) {
      transplant(tmp, tmp->right);  
      tmp->right = removing_node->right;
      tmp->right->parent = tmp;
    } else {
      x->parent = removing_node;
    }
    transplant(removing_node, tmp);
    tmp->left = removing_node->left;
    tmp->left->parent = tmp;
    tmp->color = removing_node->color;
  }
  delete removing_node;
  if (original_color == Color::BLACK) {
    removeFixUp(x);
  }
}

template <typename T>
void RBT<T>::transplant(Node* node1, Node* node2) {
  if (node1->parent == NIL) {
    m_root = node2;
  } else if (node1 == node1->parent->left) {
    node1->parent->left = node2;
  } else {
    node1->parent->right = node2;
  }
  node2->parent = node1->parent;
}

template <typename T>
typename RBT<T>::Node* RBT<T>::minimum(Node* node) {
    while (node && node->left && node != NIL && node->left != NIL) {
      node = node->left;
    }
  return node;
} 

template <typename T>
void RBT<T>::removeFixUp(Node* x) {
  while (x != m_root && x->color == Color::BLACK) {
    if (x == x->parent->left) {
      Node* sibling = x->parent->right;
      if (sibling->color == Color::RED) {
        sibling->color = Color::BLACK;
        x->parent->color = Color::RED;
        leftRotate(x->parent);
        sibling = x->parent->right;
      }
      if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
        sibling->color = Color::RED;
        x = x->parent;
      } else if (sibling->right->color == Color::BLACK) {
        sibling->left->color = Color::BLACK;
        sibling->color = Color::RED;
        rightRotate(sibling);
        sibling = x->parent->right;
      }
      sibling->color = x->parent->color;
      sibling->right->color = Color::BLACK;
      x->parent->color = Color::BLACK;
      leftRotate(x->parent);
      x = m_root;
    } else {
      Node* sibling = x->parent->left;
      if (sibling->color == Color::RED) {
        sibling->color = Color::BLACK;
        x->parent->color = Color::RED;
        rightRotate(x->parent);
        sibling = x->parent->left;
      }
      if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
        sibling->color = Color::RED;
        x = x->parent;
      } else if (sibling->left->color == Color::BLACK) {
        sibling->right->color = Color::BLACK;
        sibling->color = Color::RED;
        leftRotate(sibling);
        sibling = x->parent->left;
      }
      sibling->color = x->parent->color;
      x->parent->color = Color::BLACK;
      sibling->left->color = Color::BLACK;
      rightRotate(x->parent);
      x = m_root;      
    }
  }
  x->color = Color::BLACK;
}

template <typename T>
void RBT<T>::clear() {
  std::queue<Node*> q;
  q.push(m_root);
  while (!q.empty()) {
    Node* tmp = q.front();
    q.pop();
    if (tmp->left != NIL) {
      q.push(tmp->left);
    }
    if (tmp->right != NIL) {
      q.push(tmp->right);
    }
    delete tmp;
    tmp = nullptr;
  }
  delete NIL;
  NIL = nullptr;
}

template <typename T>
bool RBT<T>::contains(const T& val) const {
  Node* tmp = m_root;
  while (tmp != NIL) {
    if (tmp->val == val) {
      return true;
    }
    if (val < tmp->val) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
    }
  }
  return false;
}

template <typename T>
std::size_t RBT<T>::size() const {
  return size_helper(m_root);
}

template <typename T>
std::size_t RBT<T>::size_helper(Node* node) const {
  if (node == NIL) {
    return 0;
  }
  std::size_t l = size_helper(node->left);
  std::size_t r = size_helper(node->right);
  return l + r + 1;
}

template <typename T>
std::size_t RBT<T>::height() const {
  return height_helper(m_root);
}

template <typename T>
std::size_t RBT<T>::height_helper(Node* node) const {
  if (node == NIL) {
    return 0;
  }
  std::size_t l = height_helper(node->left); 
  std::size_t r = height_helper(node->left);
  return std::max(l, r) + 1; 
}

#endif //RBT_TPP_
