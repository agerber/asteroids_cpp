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
    void setSize(int size);

public:
    // Constructor for creating asteroids of different sizes
    Asteroid(int size);
    // Overloaded constructor for creating smaller asteroids from an exploded one
    Asteroid(const Asteroid& astExploded);
    // Convert radius to integer representing size: 0 = large, 1 = medium, 2 = small
    int getSize() const;
    // Generate vertices for the asteroid shape
    std::vector<sf::Vector2f> generateVertices();
    // Override the draw method to render the asteroid as a vector graphic
    void draw(sf::RenderWindow& window) override { renderVector(window); }
};

#endif
