
template<typename T>
Node<T>::Node(T val)
{
    value = val;
}

template<typename T>
T Node<T>::get_value() {
    return value;
}

template<typename T>
void Node<T>::add_child(Node<T>* child) {
    children.push_back(child);
}

template<typename T>
std::vector<Node<T>*> Node<T>::get_all_nodes() {
    std::vector<Node<T>*> result;
    std::stack<Node<T>*> stack;

    stack.push(this); // Start with the root node

    while (!stack.empty()) {
        Node<T>* current = stack.top();
        stack.pop();

        // Add current node to result
        result.push_back(current);

        // Add all children to the stack
        for (auto& child : current->children) {
            stack.push(child);
        }
    }

    return result;
}



