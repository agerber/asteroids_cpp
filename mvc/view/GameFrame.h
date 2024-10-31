#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class GameFrame {
public:
    // Constructor
    GameFrame() {
        // Initialize the window with a default size and title
        window.create(sf::VideoMode(800, 600), "Game Frame");
        window.setFramerateLimit(60); // Limit the frame rate to 60 FPS
        run();
    }

    // Destructor
    ~GameFrame() {
        if (window.isOpen()) {
            window.close();
        }
    }

    // Main game loop
    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;

    // Process events (handling window close events)
    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    // Update game state (empty for now, placeholder for future logic)
    void update() {
        // Add game update logic here if needed
    }

    // Render content
    void render() {
        window.clear();
        // Add game rendering logic here if needed
        window.display();
    }
};

#endif
