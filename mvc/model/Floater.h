#ifndef FLOATER_H
#define FLOATER_H

#include "Sprite.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

class Floater : public Sprite {
public:
    Floater() {
        // Set the team to FLOATER
        setTeam(Team::FLOATER);

        // Default values, which can be overridden in the concrete classes
        setExpiry(250);
        setColor(sf::Color::White);
        setRadius(50);

        // Set random DeltaX, DeltaY, and spin
        setDeltaX(somePosNegValue(10));
        setDeltaY(somePosNegValue(10));
        setSpin(somePosNegValue(10));

        // Cartesian points defining the shape of the polygon
        std::vector<sf::Vector2f> listPoints = {
            sf::Vector2f(5, 5),
            sf::Vector2f(4, 0),
            sf::Vector2f(5, -5),
            sf::Vector2f(0, -4),
            sf::Vector2f(-5, -5),
            sf::Vector2f(-4, 0),
            sf::Vector2f(-5, 5),
            sf::Vector2f(0, 4)
        };

        setCartesians(listPoints);
    }

    // Override the draw method for vector rendering
    void draw(sf::RenderWindow& window) override {
        renderVector(window);
    }
};

#endif
