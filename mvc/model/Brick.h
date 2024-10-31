#ifndef BRICK_H
#define BRICK_H

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <map>
#include <memory>


class Brick: public Sprite {
private:
    const int BRICK_IMAGE = 0;

public:
    Brick(sf::Vector2f upperLeftCorner, int size);

    // Overriding draw method to render the brick
    void draw(sf::RenderWindow& window) override;

    // Overriding move method - bricks do not move
    void move() override;
};

#endif
