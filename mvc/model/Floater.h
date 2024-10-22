#ifndef FLOATER_H
#define FLOATER_H

#include "Sprite.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

class Floater : public Sprite {
public:
    Floater();

    // Override the draw method for vector rendering
    void draw(sf::RenderWindow& window) override;
};

#endif
