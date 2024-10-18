#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>


class Movable {
public:
    enum class Team { FRIEND, FOE, FLOATER, DEBRIS };

    virtual ~Movable() = default;

    // Pure virtual functions that must be implemented by derived classes
    virtual void move() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    // For collision detection
    virtual sf::Vector2f getCenter() const = 0;
    virtual int getRadius() const = 0;
    virtual Team getTeam() const = 0;
    virtual bool isProtected() const = 0;
};


#endif
