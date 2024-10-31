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
    Nuke(const Falcon& falcon);

    // Override the draw method
    void draw(sf::RenderWindow& window) override;

    // A nuke is invincible until it collides 10 times
    bool isProtected() const override {
        return true;
    }

    // Override the move method
    void move() override;
};

#endif
