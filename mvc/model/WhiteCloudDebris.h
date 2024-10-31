#ifndef WHITECLOUDDEBRIS_H
#define WHITECLOUDDEBRIS_H

#include "Sprite.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class WhiteCloudDebris : public Sprite {
public:
    // Constructor
    WhiteCloudDebris(const Sprite& explodingSprite);
    void draw(sf::RenderWindow& window) override;
};

#endif
