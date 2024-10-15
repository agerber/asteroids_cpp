#ifndef FLOATER_H
#define FLOATER_H

#include <SFML/Graphics.hpp>
#include "Sprite.h"

class Floater : public Sprite {
public:
    Floater();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

/**
#include <QPainter>
#include "Sprite.h"

class Floater : public Sprite {
public:
    Floater();

    void draw(QPainter &painter) override;
};
**/

#endif // FLOATER_H
