#ifndef STAR_H
#define STAR_H

#include "Movable.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Star : public Movable {
private:
    sf::Vector2f center;
    sf::Color color;

public:
    // Constructor
    Star();

    // Draw method to render the star
    void draw(sf::RenderWindow& window) override {
        sf::CircleShape starShape(getRadius());
        starShape.setFillColor(color);
        starShape.setPosition(center.x - getRadius(), center.y - getRadius());
        window.draw(starShape);
    }

    // Implementation of Movable interface methods
    sf::Vector2f getCenter() const override {
        return center;
    }

    int getRadius() const override {
        return 1;
    }

    Team getTeam() const override {
        return Team::DEBRIS;
    }

    bool isProtected() const override {
        return false;
    }

    void move() override {
        // Do nothing
    }
};

#endif
