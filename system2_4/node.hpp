//royrachbuch@gmail.com
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <stack>

template<typename T>
class Node{
public:
    T value;
    std::vector<Node<T>*> children;
    
    Node(T val);

    T get_value();

    void add_child(Node<T>* child);

    // Function to get all nodes in the tree
    std::vector<Node<T>*> get_all_nodes();

};
#include "node.tpp"
#endif // NODE_HPP
