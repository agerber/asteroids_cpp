#ifndef ASTEROID_H
#define ASTEROID_H

#include "Sprite.h"
#include "Game.h"
#include "PolarPoint.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
#include <random>

class Asteroid : public Sprite {
private:
    const int LARGE_RADIUS = 110;

public:
    // Constructor for creating asteroids of different sizes
    Asteroid(int size) {
        // Size determines if the asteroid is large, medium, or small
        if (size == 0)
            setRadius(LARGE_RADIUS); // Large asteroid
        else
            setRadius(LARGE_RADIUS / (size * 2)); // Medium or small asteroid

        // Set as FOE
        setTeam(Team::FOE);
        setColor(sf::Color::White);

        // Set random spin and deltas
        setSpin(somePosNegValue(10));
        setDeltaX(somePosNegValue(10));
        setDeltaY(somePosNegValue(10));

        // Generate cartesian points representing vertices
        setCartesians(generateVertices());
    }

    // Overloaded constructor for creating smaller asteroids from an exploded one
    Asteroid(const Asteroid& astExploded);

    // Convert radius to integer representing size: 0 = large, 1 = medium, 2 = small
    int getSize() const {
        switch (getRadius()) {
        case 110:
            return 0;
        case 55:
            return 1;
        case 27:
            return 2;
        default:
            return 0;
        }
    }

    // Generate vertices for the asteroid shape
    std::vector<sf::Vector2f> generateVertices();

    // Override the draw method to render the asteroid as a vector graphic
    void draw(sf::RenderWindow& window) override {
        renderVector(window);
    }
};

#endif
