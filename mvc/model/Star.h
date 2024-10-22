#ifndef STAR_H
#define STAR_H

#include "Movable.h"
#include <SFML/Graphics.hpp>

class Star : public Movable {
public:
    Star();
    // Implement the required methods from the Movable interface
    void draw(sf::RenderWindow& window) override;
    sf::Vector2f getCenter() const override { return center; }
    int getRadius() const override { return 1; }
    Team getTeam() const override { return Team::DEBRIS; }
    bool isProtected() const override { return false; }
    void move() override;

private:
    sf::Vector2f center;
    sf::Color color;
};

#endif // STAR_H
