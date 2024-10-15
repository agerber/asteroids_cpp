#include "WhiteCloudDebris.h"

WhiteCloudDebris::WhiteCloudDebris(Sprite* explodingSprite) {
    setTeam(Movable::DEBRIS);

    // Load textures for animation frames
    sf::Texture texture;
    for (int i = 0; i < 9; ++i) {
        texture.loadFromFile("resources/imgs/exp/row-" + std::to_string(i / 3 + 1) +
                             "-column-" + std::to_string(i % 3 + 1) + ".png");
        rasterMap[i] = texture;
    }

    setRasterMap(rasterMap);
    setExpiry(static_cast<int>(rasterMap.size()));

    setSpin(explodingSprite->getSpin());
    setCenter(explodingSprite->getCenter());
    setDeltaX(explodingSprite->getDeltaX());
    setDeltaY(explodingSprite->getDeltaY());
    setRadius(static_cast<int>(explodingSprite->getRadius()));
}

void WhiteCloudDebris::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    int index = static_cast<int>(rasterMap.size() - getExpiry() - 1);

    if (rasterMap.find(index) != rasterMap.end()) {
        sf::Sprite sprite(rasterMap.at(index));
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(getCenter());
        sprite.setRotation(static_cast<float>(getSpin()));
        sprite.setScale(getRadius() * 2.0f / sprite.getLocalBounds().width,
                        getRadius() * 2.0f / sprite.getLocalBounds().height);
        target.draw(sprite, states);
    }
}


/**
#include "whiteclouddebris.h"

WhiteCloudDebris::WhiteCloudDebris(Sprite* explodingSprite)
{
    //DEBRIS means that this sprite is inert, and does not interact with other teams.
    setTeam(Movable::DEBRIS);
    //see readme.txt file in the resources/imgs/exp directory for how I created these assets
    
    rasterMap.insert(0, QImage(":/resources/imgs/exp/row-1-column-1.png"));
    rasterMap.insert(1, QImage(":/resources/imgs/exp/row-1-column-2.png"));
    rasterMap.insert(2, QImage(":/resources/imgs/exp/row-1-column-3.png"));
    rasterMap.insert(3, QImage(":/resources/imgs/exp/row-2-column-1.png"));
    rasterMap.insert(4, QImage(":/resources/imgs/exp/row-2-column-2.png"));
    rasterMap.insert(5, QImage(":/resources/imgs/exp/row-2-column-3.png"));
    rasterMap.insert(6, QImage(":/resources/imgs/exp/row-3-column-1.png"));
    rasterMap.insert(7, QImage(":/resources/imgs/exp/row-3-column-2.png"));
    rasterMap.insert(8, QImage(":/resources/imgs/exp/row-3-column-3.png"));

    setRasterMap(rasterMap);

    //expire it out after it has done its animation.
    setExpiry(rasterMap.size());

    //everything is relative to the exploding sprite
    setSpin(explodingSprite->getSpin());
    setCenter(explodingSprite->getCenter());
    setDeltaX(explodingSprite->getDeltaX());
    setDeltaY(explodingSprite->getDeltaY());
    setRadius(static_cast<int>(explodingSprite->getRadius()));
}

void WhiteCloudDebris::draw(QPainter& painter) {
    //we already have a simple decrement-to-zero counter with expiry; see move() method of Sprite.
    //Since draw() is being called every ~40ms, index will count-up once from 0 to 8.
    int index = rasterMap.size() - getExpiry() - 1;
    renderRaster(painter, rasterMap.value(index));
}


**/
