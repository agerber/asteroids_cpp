#ifndef NUKE_H
#define NUKE_H

#include "Sprite.h"
#include "Falcon.h"
#include <SFML/Graphics.hpp>
#include <cmath>

class Nuke : public Sprite {
private:
    static const int EXPIRE = 60;
    int nukeState = 0;

public:
    // Constructor
    Nuke(const Falcon& falcon) {
        setCenter(falcon.getCenter());
        setColor(sf::Color::Yellow);
        setExpiry(EXPIRE);
        setRadius(0);
        setTeam(Team::FRIEND);

        const double FIRE_POWER = 11.0;
        double vectorX = std::cos(falcon.getOrientation() * M_PI / 180.0) * FIRE_POWER;
        double vectorY = std::sin(falcon.getOrientation() * M_PI / 180.0) * FIRE_POWER;

        // Fire force: falcon inertia + fire-vector
        setDeltaX(falcon.getDeltaX() + vectorX);
        setDeltaY(falcon.getDeltaY() + vectorY);
    }

    // Override the draw method
    void draw(sf::RenderWindow& window) override {
        sf::CircleShape nukeShape(getRadius());
        nukeShape.setOutlineColor(getColor());
        nukeShape.setOutlineThickness(1);
        nukeShape.setFillColor(sf::Color::Transparent);
        nukeShape.setPosition(getCenter().x - getRadius(), getCenter().y - getRadius());
        window.draw(nukeShape);
    }

    // A nuke is invincible until it collides 10 times
    bool isProtected() const override {
        return true;
    }

    // Override the move method
    void move() override {
        Sprite::move();

        if (getExpiry() % (EXPIRE / 6) == 0) {
            nukeState++;
        }

        switch (nukeState) {
        // Travelling
        case 0:
            setRadius(2);
            break;
        // Exploding
        case 1:
        case 2:
        case 3:
            setRadius(getRadius() + 16);
            break;
        // Imploding
        case 4:
        case 5:
        default:
            setRadius(getRadius() - 22);
            break;
        }
    }
};

#endif
