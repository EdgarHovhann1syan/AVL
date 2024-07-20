#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>

template <typename T>
class AVL 
{
private:
    struct Node {
        T m_data;
        Node* m_left;
        Node* m_right;
        Node(const T& data) : m_data(data), m_left(nullptr), m_right(nullptr) {}
    };
public:
    AVL();
    const T& findMin() const;
    T& findMin();
    const T& findMax() const;
    T& findMax();

    const Node* find(const T& data) const;
    Node* find(const T& data);
    bool insert(const T& data);
    bool remove(const T& data);

    //traversals
    void preOrderTraversal() const;
    void inOrderTraversal() const;
    void postOrderTraversal() const;
    void levelOrderTraversal() const;

    // Getters for successor and predecessor
    const T& getSuccessor(const T& val) const;
    T& getSuccessor(const T& val);
    const T& getPredecessor(const T& val) const;
    T& getPredecessor(const T& val);

    std::size_t getHeight() const;




private: //helper functions
    Node* findHelper(Node* node, const T& data) const;
    Node* insertHelper(Node* node, const T& data);
    Node* removeHelper(Node* node, const T& data);
    T& findMinHelper(Node* node) const;
    T& findMaxHelper(Node* node) const;

    void preOrderHelper(const Node* node) const;
    void inOrderHelper(const Node* node) const;
    void postOrderHelper(const Node* node) const;
    void levelOrderHelper(const Node* node) const;
    void handleCurrentLevel(const Node* node, int level) const;
    Node* ll_case(Node* node);
    Node* rr_case(Node* node);
    Node* lr_case(Node* node);
    Node* rl_case(Node* node);

    int getBalancingFactor(Node* node) const;

    std::size_t getHeightHelper(const Node* node) const;

    

private:
    Node* m_root;



};

#include "avl_tree.tpp"

#endif //AVL_TREE_H