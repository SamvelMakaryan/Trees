#ifndef TRIE_TPP_
#define TRIE_TPP_
#include "Trie.hpp"

Trie::Node::Node()
: is_word(false) {}

Trie::Trie()
: m_root(new Node) {}

Trie::Trie(std::initializer_list<std::string> init) {
    for (auto& i : init) {
        insert(i);
    }
}

Trie::Trie(Trie&& oth) noexcept 
: m_root(oth.m_root)
{
    oth.m_root = nullptr;
}

Trie::Trie(const Trie& oth) 
: m_root(new Node)
{
    copy_helper(m_root, oth.m_root);
}

Trie::~Trie() {
    clear();
}

void Trie::insert(const std::string& word) {
    if (word.empty()) {
        return;
    }
    if (!m_root) {
        m_root = new Node;
    }
    Node* node = m_root;
    for (char c : word) {
        if (node->m_map.find(c) == node->m_map.end()) {
            node->m_map[c] = new Node();
        }
        node = node->m_map[c];
    }
    node->is_word = true;
}

bool Trie::contains(const std::string& word) const {
    if (word.empty() || !m_root) {
        return false;
    }
    Node* node = m_root;
    for (char c : word) {
        if (node->m_map.find(c) == node->m_map.end()) {
            return false;
        }
        node = node->m_map[c];
    }
    return true;
}

void Trie::remove(const std::string& word) {
    remove_helper(m_root, word, 0);
}

bool Trie::remove_helper(Node* node, const std::string& word, int depth) {
    if (!node) {
        return false;
    }
    if (depth == word.size()) {
        if (!node->is_word) {
            return false;
        }
        node->is_word = false;
        return node->m_map.empty();
    }
    auto it = node->m_map.find(word[depth]);
    if (it == node->m_map.end()) {
        return false;
    }
    bool should_be_deleted = remove_helper(it->second, word, depth + 1);
    if (should_be_deleted) {
        Node* tmp = it->second;
        node->m_map.erase(it);
        delete tmp;
        return node->m_map.empty();
    }
    return false;
}

void Trie::clear() {
    clear_helper(m_root);
    m_root = nullptr;
}

void Trie::clear_helper(Node* node) {
    if (!node) {
        return;
    }
    for (auto& child : node->m_map) {
        clear_helper(child.second);    
    }
    delete node;
}

void Trie::print() const {
    print_helper(m_root, "");
}

void Trie::print_helper(Node* node, const std::string& word) const {
    if (!node) {
        return;
    }
    if (node->is_word) {
        std::cout << word << std::endl;
    }
    for (auto& i : node->m_map) {
        print_helper(i.second, word + i.first);
    }
}

void Trie::printLevelorder() const {
    if (!m_root) {
        return;
    }
    std::queue<Node*> q;
    q.push(m_root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            Node* tmp = q.front();
            q.pop();
            for (auto& i : tmp->m_map) {
                std::cout << i.first << " ";
                q.push(i.second);
            }
            std::cout << "- ";
        }
        std::cout << std::endl;
    }
}

std::size_t Trie::size() const {
    return size_helper(m_root);
}
std::size_t Trie::size_helper(Node* node) const {
    if (!node) {
        return 0;
    }
    std::size_t count = 0;
    if (node->is_word) {
        ++count;
    }
    for (auto& i : node->m_map) {
        count += size_helper(i.second);
    }
    return count;
}

bool Trie::empty() const {
    if (!m_root) {
        return true;
    }
    return false;
}

void Trie::copy_helper(Node* node, Node* oth) {
    node->is_word = oth->is_word;
    for (auto& i : oth->m_map) {
        Node* new_node = new Node;
        node->m_map[i.first] = new_node;
        copy_helper(new_node, i.second);
    }
}

bool Trie::startsWith(const std::string& word) const {
    if (word.empty() || !m_root) {
        return false;
    }
    Node* node = m_root;
    for (char c : word) {
        if (node->m_map.find(c) == node->m_map.end()) {
            return false;
        }
        node = node->m_map[c];
    }
    return true;
}

#endif //TRIE_TPP_