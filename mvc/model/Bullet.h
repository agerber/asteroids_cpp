#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h" // Ensure Sprite.h is correctly included
#include "Falcon.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Bullet : public Sprite {
public:
    Bullet(const Falcon& falcon) {
        // Set as a friendly unit
        setTeam(Team::FRIEND);
        setColor(sf::Color::Orange);

        // Bullet expires after 20 frames
        setExpiry(20);
        setRadius(6);

        // Position is relative to the Falcon's position
        setCenter(falcon.getCenter());

        // Set bullet orientation to Falcon's orientation
        setOrientation(falcon.getOrientation());

        const double FIRE_POWER = 35.0;
        double vectorX = std::cos(getOrientation() * M_PI / 180.0) * FIRE_POWER;
        double vectorY = std::sin(getOrientation() * M_PI / 180.0) * FIRE_POWER;

        // Fire force: Falcon inertia + fire-vector
        setDeltaX(falcon.getDeltaX() + vectorX);
        setDeltaY(falcon.getDeltaY() + vectorY);

        // Apply kick-back to the Falcon
        const double KICK_BACK_DIVISOR = 36.0;
        Falcon& mutableFalcon = const_cast<Falcon&>(falcon);
        mutableFalcon.setDeltaX(falcon.getDeltaX() - vectorX / KICK_BACK_DIVISOR);
        mutableFalcon.setDeltaY(falcon.getDeltaY() - vectorY / KICK_BACK_DIVISOR);

        // Define the points on a cartesian grid
        std::vector<sf::Vector2f> listPoints = {
            sf::Vector2f(0, 3),   // Top point
            sf::Vector2f(1, -1),  // Right bottom
            sf::Vector2f(0, 0),   // Center
            sf::Vector2f(-1, -1)  // Left bottom
        };

        setCartesians(listPoints);
    }

    // Override the draw method to render the bullet as a vector graphic
    void draw(sf::RenderWindow& window) override {
        renderVector(window);
    }
};

#endif
