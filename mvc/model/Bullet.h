#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h" // Ensure Sprite.h is correctly included
#include "Falcon.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Bullet : public Sprite {
public:
    Bullet(const Falcon& falcon) ;

    // Override the draw method to render the bullet as a vector graphic
    void draw(sf::RenderWindow& window) override;
};

#endif
