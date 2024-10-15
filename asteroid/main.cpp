#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(Game::DIM.x, Game::DIM.y), "Asteroids Game");
    Game game;

    //game.setGraphics();  // Optional setup if needed
    game.run();  // Start the game logic thread

    // Main loop to handle events and rendering
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.stop();  // Stop the game logic thread
                window.close();
            }
            // Forward key events to the game object
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                game.handleEvent(event);
            }
        }

        // Update the game and render the current state
        game.update();
        game.render(window);
    }

    std::cout << "This is a test" << std::endl;

    return 0;
}


/**
#include <QApplication>
#include <QThread>
#include "Game.h"
#include "QDebug"
#include <QStringList>

#define QDEBUGS QStringList

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // typical Qt application start
    // call QObject threading object to move object to another thread
  //  GamePanel *gamePanel= new GamePanel(nullptr, Game::DIM);
    // add key listener to the game panel
  //  gamePanel->setMinimumSize(Game::DIM.width(), Game::DIM.height());


     auto game = new Game();
     game->start();

     QDEBUGS() << "this is a test";

    return app.exec();
}
**/
