#ifndef NEWWALLFLOATER_H
#define NEWWALLFLOATER_H

#include "Floater.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

class NewWallFloater : public Floater {
public:
    // Constants
    static int SPAWN_NEW_WALL_FLOATER();

    // Constructor
    NewWallFloater() {
        // Set color to maroon
        setColor(sf::Color(186, 0, 22));
        // Set expiry time
        setExpiry(230);
    }
};

#endif
