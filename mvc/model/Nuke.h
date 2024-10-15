#ifndef NUKE_H
#define NUKE_H

#include "Sprite.h"
#include "Falcon.h"
#include <SFML/Graphics.hpp>

class Nuke : public Sprite {
public:
    Nuke(Falcon* falcon);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isProtected() const override;
    void move() override;

private:
    static const int EXPIRE = 60;
    int nukeState = 0;
};

/**
#include <QGraphicsItem>

#include "Sprite.h"
#include "Falcon.h"

class Nuke : public Sprite {

public:
    Nuke(Falcon *falcon);
    void draw(QPainter &painter) override;
    bool isProtected() override;
    void move() override;

private:
    static const int EXPIRE = 60;
    int nukeState = 0;

};
**/

#endif // 
