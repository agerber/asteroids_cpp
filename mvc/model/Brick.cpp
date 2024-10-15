#pragma once

#include <Brick.h>



#include <iostream>

Brick::Brick(sf::Vector2f upperLeftCorner, int size) {
    sf::Vector2f center(upperLeftCorner.x + size / 2.0f, upperLeftCorner.y + size / 2.0f);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/imgs/brick/Brick_Block100.png")) {
        std::cerr << "Failed to load texture\n";
    }

    std::map<int, sf::Texture> rasterMap;
    rasterMap[BRICK_IMAGE] = texture;
    // Store or process rasterMap if needed
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw logic can go here using SFML if needed
}

void Brick::move() {
    // A brick does not move, so this method intentionally does nothing.
}

/**

#include <QPoint>
#include <QImage>
#include <map>
#include "Sprite.h"


//The size of this brick is always square!
//we use upperLeftCorner because that is the origin when drawing graphics in Java
Brick::Brick(QPoint upperLeftCorner, int size) {

    //you can shoot to destroy the wall which yields big points
    setTeam(Movable::FOE);

    setCenter(QPoint(upperLeftCorner.x() + size/2, upperLeftCorner.y() + size/2));

    setRadius(size/2);

    //As this sprite does not animate or change state, we could just store a QImage as a member, but
    //since we already have a rasterMap in the Sprite class, we might as well be consistent for all raster sprites
    // and use it.
    QMap<int, QImage> rasterMap;
    //brick from Mario Bros
    QString path = QString(":/resources/imgs/brick/Brick_Block100.png");
    rasterMap.insert(BRICK_IMAGE, loadGraphic(path));

    setRasterMap(rasterMap);

}

void Brick::draw(QPainter &painter) {
    renderRaster(painter, getRasterMap()[BRICK_IMAGE]);
    //if you uncomment these, you can see how collision works. Feel free to remove these two lines.
    //g.setColor(Color.LIGHT_GRAY);
    //g.drawOval(getCenter().x - getRadius(), getCenter().y - getRadius(), getRadius() *2, getRadius() *2);
}

//the reason we override the move method is to skip the logic contained in super-class Sprite move() method
//which is laborious, thereby gaining slight performance
void Brick::move() {
    //do NOT call super.move() and do nothing; a brick does not move.
}

**/
