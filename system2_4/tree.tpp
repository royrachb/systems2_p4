#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <memory>
template<typename T, int K>
void Tree<T, K>::add_root( Node<T>& node) {
    root = new Node<T>(node);
}



template<typename T, int K>
void Tree<T, K>::add_sub_node( Node<T>& parent,  Node<T>& child) {
    if (!root) return;

    Node<T>* parent_node = find_node(root, parent.get_value());
    if (parent_node && parent_node->children.size() < K) {
        parent_node->add_child(&child);
    }
}


template<typename T, int K>
Node<T>* Tree<T, K>::find_node(Node<T>* current, const T& value) const { // Change here    if (!current) return nullptr;
    if (current->get_value() == value) return current;
    for (auto& child : current->children) {
        Node<T>* found = find_node(child, value);
        if (found) return found;
    }
    return nullptr;
}
// PreOrderIterator implementations

// Constructor initializes the iterator with the root node and DFS flag
template<typename T, int K>
Tree<T, K>::PreOrderIterator::PreOrderIterator(Node<T>* root){
    if (root) {
        next.push(root);  // Add root to the stack if it is not null
    }
}

// Dereference operator returns the current node at the top of the stack
template<typename T, int K>
Node<T>* Tree<T, K>::PreOrderIterator::operator*() 
{
    return next.top();
}

// Increment operator moves the iterator to the next node in pre-order traversal
template<typename T, int K>
typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
    Node<T>* currentNode = next.top();  // Get the current node
    next.pop();  // Remove the current node from the stack

    auto& children = currentNode->children;
    // Add children to the stack in reverse order to maintain pre-order traversal
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it != nullptr) {
            next.push(*it);
        }
        else {
            // Throw an error if a null or invalid child is encountered
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
template<typename T, int K>
bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !next.empty();  // The iterators are not equal if the stack is not empty
}

// Returns an iterator to the beginning of the pre-order traversal
template<typename T, int K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() const {
    return PreOrderIterator(root);  // Use DFS if maxDegree > 2
}

// Returns an iterator to the end of the pre-order traversal
template<typename T, int K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() const {
    return PreOrderIterator(nullptr);
}


template<typename T, int K>
Tree<T, K>::PostOrderIterator::PostOrderIterator(Node<T>* root, bool useDFS) : useDFS(useDFS)
{
    if (useDFS) {
        if (root) {
            dfsStack.push(root);  // Add root to the DFS stack if it is not null
        }
    }

    else {
        if (root) {
            stack.push({root, false});  // Add root to the stack if it is not null
            expandTop();  // Expand the stack to process the first node
        }
    }
}

template<typename T, int K>
void Tree<T, K>::PostOrderIterator::expandTop() {
    while (!stack.empty()) {
        auto& [node, visited] = stack.top();
        if (visited) {
            stack.pop();
            dfsStack.push(node);  // Push the node to the DFS stack
            break;
        }
        else {
            stack.pop();
            stack.push({node, true});  // Mark the node as visited
            auto& children = node->children;

            // Add children to the stack in reverse order
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                if (*it != nullptr) {
                    stack.push({*it, false});
                }
                else {
                    // Throw an error if a null or invalid child is encountered
                    throw std::runtime_error("Error: Encountered null or invalid child node!");
                }
            }
        }
    }
}

template<typename T, int K>
Node<T>* Tree<T, K>::PostOrderIterator::operator*() {
    return dfsStack.top();  // Return the node at the top of the DFS stack
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
    if (useDFS) {
        Node<T>* currentNode = dfsStack.top();
        dfsStack.pop();  // Remove the current node from the DFS stack
        auto& children = currentNode->children;
        // Add children to the DFS stack in reverse order
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                dfsStack.push(*it);
            } else {
                // Throw an error if a null or invalid child is encountered
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
    }

    else {
        dfsStack.pop();  // Remove the current node from the stack
        expandTop();  // Process the next node in the stack
    }
    return *this;
}


template<typename T, int K>
bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !dfsStack.empty();  // The iterators are not equal if the DFS stack is not empty
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() const {
    return PostOrderIterator(root, false);  // Use DFS if maxDegree > 2
}



template<typename T, int K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() const {
    return PostOrderIterator(nullptr, maxDegree > 2);  // Use DFS if maxDegree > 2
}
// BFSIterator implementations

// Constructor initializes the iterator with the root node
template<typename T, int K>
Tree<T, K>::BFSIterator::BFSIterator(Node<T>* root) {
    if (root) {
        queue.push(root);  // Add root to the queue if it is not null
    }
}

// Dereference operator returns the current node at the front of the queue
template<typename T, int K>
Node<T>* Tree<T, K>::BFSIterator::operator*() {
    return queue.front();
}

// Increment operator moves the iterator to the next node in BFS order
template<typename T, int K>
typename Tree<T, K>::BFSIterator& Tree<T, K>::BFSIterator::operator++() {
    Node<T>* node = queue.front();  // Get the current node
    queue.pop();  // Remove the current node from the queue
    auto& children = node->children;
    for (auto& child : children) {
        if (child != nullptr) {
            queue.push(child);  // Add each non-null child to the queue
        }
        else {
            // Throw an error if a null or invalid child is encountered
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
template<typename T, int K>
bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
    return !queue.empty();  // The iterators are not equal if the queue is not empty
}

// Returns an iterator to the beginning of the BFS traversal
template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs() const {
    return BFSIterator(root);  // Return a BFSIterator starting from the root
}

// Returns an iterator to the end of the BFS traversal
template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs() const {
    return BFSIterator(nullptr);  // Return a BFSIterator representing the end
}

// Returns an iterator to the beginning of the BFS traversal (default)
template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::begin() const {
    return begin_bfs();
}

// Returns an iterator to the end of the BFS traversal (default)
template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::end() const {
    return end_bfs();
}

template<typename T, int K>
Tree<T, K>::InOrderIterator::InOrderIterator(Node<T>* root) : current(root) {
    push_left(current);

    if (!stack.empty()) {
        current = stack.top();
        stack.pop();
    }
}

template<typename T, int K>
bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return current != other.current;
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
    if (current) {
        if (current->children.size() > 1 && current->children[1]) {
            push_left(current->children[1]);
        }

        if (!stack.empty()) {
            current = stack.top();
            stack.pop();
        } else {
            current = nullptr;
        }
    }

    return *this;
}

template<typename T, int K>
void Tree<T, K>::InOrderIterator::push_left(Node<T>* node) {

    while (node) {
        stack.push(node);
        if (!node->children.empty()) {
            node = node->children[0];
        } else {
            node = nullptr;
        }
    }
}

template<typename T, int K>
Node<T>* Tree<T, K>::InOrderIterator::operator*() const {
    return current;
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_in_order() const {
    return InOrderIterator(root);  // Use DFS if maxDegree > 2
}

// Returns an iterator to the end of the pre-order traversal
template<typename T, int K>
typename Tree<T, K>::InOrderIterator Tree<T, K>::end_in_order() const {
    return InOrderIterator(nullptr);
}


// DFSIterator implementations

template<typename T, int K>
Tree<T, K>::DFSIterator::DFSIterator(Node<T>* root) {
    if (root) {
        next.push(root);  // Add root to the stack if it is not null
    }
}

template<typename T, int K>
Node<T>* Tree<T, K>::DFSIterator::operator*() {
    return next.top();
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
    Node<T>* currentNode = next.top();  // Get the current node
    next.pop();  // Remove the current node from the stack

    auto& children = currentNode->children;
    // Add children to the stack in reverse order to maintain DFS order
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it != nullptr) {
            next.push(*it);
        }
        else {
            // Throw an error if a null or invalid child is encountered
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

template<typename T, int K>
bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator& other) const {
    return !next.empty();  // The iterators are not equal if the stack is not empty
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs() const {
    return DFSIterator(root);  // Return a DFSIterator starting from the root
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs() const {
    return DFSIterator(nullptr);  // Return a DFSIterator representing the end
}

template<typename T, int K>
Tree<T,K>* Tree<T, K>::myHeap()
{
 std::vector<Node<T>*> all_nodes = root->get_all_nodes();

    // Extract values from nodes
    std::vector<T> values;
    for (auto node : all_nodes) {
        values.push_back(node->get_value());
    }

    // Sort the values to create a min-heap
    std::sort(values.begin(), values.end());

    // Create a new vector of nodes for the min-heap
    std::vector<Node<T>*> heap_nodes;
    for (const auto& value : values) {
        heap_nodes.push_back(new Node<T>(value));
    }

    // Construct a complete binary tree from sorted values
    std::queue<Node<T>*> node_queue;
    node_queue.push(heap_nodes[0]);
    size_t index = 1;

    while (index < heap_nodes.size()) {
        Node<T>* current = node_queue.front();
        node_queue.pop();

        for (int i = 0; i < K && index < heap_nodes.size(); ++i) {
            current->add_child(heap_nodes[index]);
            node_queue.push(heap_nodes[index]);
            ++index;
        }
    }

    // Return the new tree
    return new Tree<T, K>(heap_nodes[0]);
}
