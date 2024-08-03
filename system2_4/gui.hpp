#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include "node.hpp"

template<typename T>
class Gui {
public:
    Gui(Node<T>* root) : root(root) {}
    void run();

private:
    Node<T>* root;
    void draw_node(sf::RenderWindow& window, Node<T>* node, float x, float y, float x_offset, float y_offset);
};

#include "gui.tpp"
#endif // GUI_HPP
