#ifndef BINARY_SEARCH_TREE_TPP
#define BINARY_SEARCH_TREE_TPP

#include <stdexcept>
#include <iostream>
template <typename T>
BST<T>::BST() 
    : m_root(nullptr)
{
}

template <typename T>
const T& BST<T>::findMin() const 
{
    const Node* node = m_root;
    if (node == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    while (node->m_left != nullptr) {
        node = node->m_left;
    }
    return node->m_data;
}

template <typename T>
T& BST<T>::findMin() 
{
    Node* node = m_root;
    if (node == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    while (node->m_left != nullptr) {
        node = node->m_left;
    }
    return node->m_data;
}

template <typename T>
const T& BST<T>::findMax() const 
{
    const Node* node = m_root;
    if (node == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    while (node->m_right != nullptr) {
        node = node->m_right;
    }
    return node->m_data;
}

template <typename T>
T& BST<T>::findMax() 
{
    Node* node = m_root;
    if (node == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    while (node->m_right != nullptr) {
        node = node->m_right;
    }
    return node->m_data;
}


template <typename T>
typename BST<T>::Node* BST<T>::findHelper( BST<T>::Node* node, const T& data) const
{
    if (node == nullptr) {
        return nullptr;
    }
    if (data > node->m_data) {
        return findHelper(node->m_right, data);
    } else if (data < node->m_data) {
        return findHelper(node->m_left, data);
    } else {
        return node;
    }
}
template <typename T>
typename BST<T>::Node* BST<T>::find(const T& data)
{
    return findHelper(m_root, data);
}

template <typename T>
const typename BST<T>::Node* BST<T>::find(const T& data) const
{
    return findHelper(m_root, data);
}

template <typename T>
bool BST<T>::insert(const T& data)
{
    if(!find(data))
    {
    m_root = insertHelper(m_root, data);
    return true; 
    }
    return false;
}

template <typename T>
typename BST<T>::Node* BST<T>::insertHelper(typename BST<T>::Node* node, const T& data)
{
    if (node == nullptr) {
        return new Node(data);
    }
    if (data > node->m_data) {
        node->m_right = insertHelper(node->m_right, data);
    } else if (data < node->m_data) {
        node->m_left = insertHelper(node->m_left, data);
    }
    return node;
}

template <typename T>
T& BST<T>::findMinHelper(Node* node) const
{
    if(node->m_left)
    {
        return findMinHelper(node->m_left);
    }
    return node->m_data;
}

template <typename T>
T& BST<T>::findMaxHelper(Node* node) const
{
    if(node->m_right)
    {
        return findMaxHelper(node->m_right);
    }
    return node->m_data;
}
template <typename T>
typename BST<T>::Node* BST<T>::removeHelper(Node* node, const T& data)
{
    if(node == nullptr)
    {
        return node;
    }
    if(data < node->m_data)
    {
        node->m_left = removeHelper(node->m_left, data);
    } else if(data > node->m_data)
    {
        node->m_right = removeHelper(node->m_right, data);
    } else 
    {
        if(node->m_left == nullptr)
        {
            Node* temp = node->m_right;
            delete node;
            return temp;
        }
        if(node->m_right == nullptr)
        {
            Node* temp = node->m_left;
            delete node;
            return temp;
        }
        T minValue = findMinHelper(node->m_right);
        node->m_data = minValue;
        node->m_right = removeHelper(node->m_right, data);
    }
    return node;
}

template <typename T>
bool BST<T>::remove(const T& data)
{
    if(find(data))
    {
        m_root = removeHelper(m_root, data);
        return true;
    }
    return false;
}


template <typename T>
void BST<T>::preOrderHelper(const Node* node) const 
{
    if(node)
    {
        std::cout << node->m_data << "  ";
        preOrderHelper(node->m_left);
        preOrderHelper(node->m_right);
    }
}

template <typename T>
void BST<T>::inOrderHelper(const Node* node) const 
{
    if(node)
    {
        inOrderHelper(node->m_left);
        std::cout << node->m_data << "  ";
        inOrderHelper(node->m_right);
    }
}

template <typename T>
void BST<T>::postOrderHelper(const Node* node) const
{
    if(node)
    {
        postOrderHelper(node->m_left);
        postOrderHelper(node->m_right);
        std::cout << node->m_data << "  ";
    }
}

template <typename T>
void BST<T>::levelOrderHelper(const Node* node) const
{
    int h = getHeightHelper(node);
    for(int i = 1; i <= h; ++i)
    {
        handleCurrentLevel(node, i);
    }
}

template <typename T>
void BST<T>::handleCurrentLevel(const Node* node, int level) const 
{
    if(!node)
    {
        return;
    }
    if(level == 1)
    {
        std::cout << node->m_data << "  ";
    } else if(level > 1)
    {
        handleCurrentLevel(node->m_left, level - 1);
        handleCurrentLevel(node->m_right, level - 1);
    }
}

template <typename T>
void BST<T>::levelOrderTraversal() const
{
    levelOrderHelper(m_root);
}
template <typename T>
void BST<T>::preOrderTraversal() const 
{
    preOrderHelper(m_root);
}

template <typename T>
void BST<T>::inOrderTraversal() const 
{
    inOrderHelper(m_root);
}

template <typename T>
void BST<T>::postOrderTraversal() const
{
    postOrderHelper(m_root);
}


template <typename T>
const T& BST<T>::getSuccessor(const T& val) const 
{
    Node* tmp = find(val);
    if(tmp == nullptr)
    {
        throw std::runtime_error("Successor not found");
    }

    if(tmp->getRight())
    {
        return findMin(tmp->getRight());
    }

    Node* ancestor = m_root;
    Node* successor = nullptr;
    while(ancestor != tmp)
    {
        if(val < ancestor->m_data)
        {
            successor = ancestor;
            ancestor = ancestor->m_left;
        } else
        {
            ancestor = ancestor->m_right;
        }
    }
    return successor->data;
}

template <typename T>
T& BST<T>::getSuccessor(const T& val) 
{
    const Node* tmp = find(val);
    if(tmp == nullptr)
    {
        throw std::runtime_error("Successor not found");
    }

    if(tmp->m_right)
    {
        return findMinHelper(tmp->m_right);
    }

    Node* ancestor = m_root;
    Node* successor = nullptr;
    while(ancestor != tmp)
    {
        if(val < ancestor->m_data)
        {
            successor = ancestor;
            ancestor = ancestor->m_left;
        } else
        {
            ancestor = ancestor->m_right;
        }
    }
    return successor->m_data;
}


template <typename T>
const T& BST<T>::getPredecessor(const T& val) const
{
    const Node* tmp = find(val);
    if(tmp == nullptr)
    {
        throw std::runtime_error("Predecessor not found");
    }

    if(tmp->m_left)
    {
        return findMaxHelper(tmp->m_left);
    }

    Node* ancestor = m_root;
    Node* predecessor = nullptr;
    while(ancestor != tmp)
    {
        if(val < ancestor->m_data)
        {
            ancestor = ancestor->m_left;
        } else 
        {
            predecessor = ancestor;
            ancestor = ancestor->m_right;
        }
    }
    return predecessor->m_data;
}

template <typename T>
T& BST<T>::getPredecessor(const T& val)
{
    const Node* tmp = find(val);
    if(tmp == nullptr)
    {
        throw std::runtime_error("Predecessor not found");
    }

    if(tmp->m_left)
    {
        return findMaxHelper(tmp->m_left);
    }

    Node* ancestor = m_root;
    Node* predecessor = nullptr;
    while(ancestor != tmp)
    {
        if(val < ancestor->m_data)
        {
            ancestor = ancestor->m_left;
        } else 
        {
            predecessor = ancestor;
            ancestor = ancestor->m_right;
        }
    }
    return predecessor->m_data;
}

template <typename T>
std::size_t BST<T>::getHeightHelper(const Node* node) const 
{
    if(!node)
    {
        return 0;
    }
    return std::max(getHeightHelper(node->m_left), getHeightHelper(node->m_right)) + 1;
}
template <typename T>
std::size_t BST<T>::getHeight() const 
{
    return getHeightHelper(m_root);
}
#endif // BINARY_SEARCH_TREE_TPP
