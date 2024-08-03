#include "gui.hpp"
#include <sstream>
#include <iostream>

template<typename T>
void Gui<T>::run() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Display with SFML");

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf")) {
        std::cerr << "Failed to load font \"DejaVuSans.ttf\"" << std::endl;
        return;
    }

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the tree starting from the root node
        draw_node(window, root, 400, 50, 150, 100);

        // Update the window
        window.display();
    }
}

template<typename T>
void Gui<T>::draw_node(sf::RenderWindow& window, Node<T>* node, float x, float y, float x_offset, float y_offset) {
    if (!node) return;

    // Draw the node's value
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf")) {
        std::cerr << "Failed to load font \"DejaVuSans.ttf\"" << std::endl;
        return;
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);

    std::stringstream ss;
    ss << node->get_value();
    text.setString(ss.str());

    window.draw(text);

    // Draw lines to children and recursively draw each child node
    for (auto* child : node->children) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x + 10, y + 20)),
            sf::Vertex(sf::Vector2f(x + x_offset, y + y_offset))
        };

        window.draw(line, 2, sf::Lines);

        draw_node(window, child, x + x_offset, y + y_offset, x_offset / 2, y_offset);
        x_offset = -x_offset; // Alternate child positions
    }
}
