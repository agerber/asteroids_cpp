#ifndef BULLET_H
#define BULLET_H


#include "Sprite.h"
#include "Falcon.h"
#include <SFML/Graphics.hpp>

class Bullet : public Sprite {
public:
    Bullet(Falcon* falcon);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

/**
#include "Sprite.h"
#include "Falcon.h"

class Bullet: public Sprite
{
public:
    Bullet(Falcon* falcon);

    void draw(QPainter& painter) override;
};
**/

#endif // BULLET_H
