#ifndef SHIELDFLOATER_H
#define SHIELDFLOATER_H

#include "Floater.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

class ShieldFloater : public Floater {
public:
    // Spawn every 25 seconds
    static int SPAWN_SHIELD_FLOATER();

    ShieldFloater() {
        setColor(sf::Color::Cyan);
        setExpiry(260);
    }

};




#endif
