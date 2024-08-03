#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "node.hpp"
#include "gui.hpp"

#include <vector>
#include <queue>
#include <stack>

template<typename T, int K = 2>
class Tree {
private:
    Node<T>* root;
    Node<T>* find_node(Node<T>* current, const T& value) const; // Change here
public:
        // Default constructor initializes a tree with a maximum degree of 2
    Tree() : root(nullptr), maxDegree(2) {}

    // Constructor that allows setting a custom maximum degree for the tree
    Tree(unsigned int degree) : root(nullptr), maxDegree(degree) {}

    Tree(Node<T>* node) : root(node), maxDegree(2) {}

    // Destructor
    // Destructor for the Tree class
    ~Tree() {
        clear(root);
    }

    // Helper function to delete all nodes in the tree
    void clear(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        
        // Recursively delete all children nodes
        for (auto child : node->children) {
            clear(child);
        }
        
        // Delete the current node
        delete node;
    }
    Tree<T,K>* myHeap();

    void add_root( Node<T>& node);
    void add_sub_node( Node<T>& parent,  Node<T>& child);
    int maxDegree;
    class PreOrderIterator {
    private:
        std::stack<Node<T>*> next;  // Stack to manage the pre-order traversal.

    public:

        PreOrderIterator(Node<T>* root);


        Node<T>* operator*();
        PreOrderIterator& operator++();

        bool operator!=(const PreOrderIterator& other) const;
    };

    PreOrderIterator begin_pre_order() const;

    PreOrderIterator end_pre_order() const;

    class PostOrderIterator {
    private:
        std::stack<std::pair<Node<T>*, bool>> stack;  // Stack to manage the post-order traversal.
        std::stack<Node<T>*> dfsStack;  // Stack to manage DFS traversal.
        bool useDFS;  // Flag to determine whether to use DFS.

      
        void expandTop();

    public:

         PostOrderIterator( Node<T>* root, bool useDFS);

        Node<T>* operator*();

     
        PostOrderIterator& operator++();

     
        bool operator!=(const PostOrderIterator& other) const;
    };


    PostOrderIterator begin_post_order() const;

    /**
     * @brief Gets the end iterator for post-order traversal.
     * @return PostOrder iterator pointing to the end of the traversal.
     */
    PostOrderIterator end_post_order() const;

    /**
     * @brief BFS (Breadth-First Search) iterator class for traversing the tree.
     */
    class BFSIterator {
    private:
        std::queue<Node<T>*> queue;  // Queue to manage the BFS traversal.

    public:
        /**
         * @brief Constructor initializes the iterator with the root node.
         * @param root Pointer to the root node.
         */
        explicit BFSIterator(Node<T>* root);

        /**
         * @brief Dereference operator to access the current node.
         * @return Pointer to the current node.
         */
        Node<T>* operator*();

        BFSIterator& operator++();

 
        bool operator!=(const BFSIterator& other) const;
    };

    BFSIterator begin_bfs() const;


    BFSIterator end_bfs() const;

  
    BFSIterator begin() const;

    BFSIterator end() const;

    class InOrderIterator 
    {
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;

        void push_left(Node<T>* node);

    public:
        InOrderIterator(Node<T>* root);

        bool operator!=(const InOrderIterator& other) const;
        InOrderIterator& operator++();
        Node<T>* operator*() const;
    };

    InOrderIterator begin_in_order() const;


    InOrderIterator end_in_order() const;
    // Friend function definition within the class

    friend std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree)
     {
        Gui gui((tree.root));
        gui.run();  // Use GUI to render the tree
        return os;
    }

    class DFSIterator {
    private:
        std::stack<Node<T>*> next;  // Stack to manage the DFS traversal.

    public:

        explicit DFSIterator(Node<T>* root);


        Node<T>* operator*();


        DFSIterator& operator++();


        bool operator!=(const DFSIterator& other) const;
    };

    DFSIterator begin_dfs() const;

    DFSIterator end_dfs() const;


    };
#include "tree.tpp"

#endif // TREE_HPP