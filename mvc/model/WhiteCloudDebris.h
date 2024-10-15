#ifndef WHITECLOUDDEBRIS_H
#define WHITECLOUDDEBRIS_H


#include <SFML/Graphics.hpp>
#include <map>
#include "Sprite.h"

class WhiteCloudDebris : public Sprite {
public:
    WhiteCloudDebris(Sprite* explodingSprite);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::map<int, sf::Texture> rasterMap;
};

/**
#include <QObject>
#include <QPoint>
#include <QPainter>

#include "Sprite.h"

class WhiteCloudDebris : public Sprite {
    Q_OBJECT

public:
    WhiteCloudDebris(Sprite* explodingSprite);

    void draw(QPainter& painter) override;

private:
    QMap<int, QImage> rasterMap;
};
**/

#endif // WHITECLOUDDEBRIS_H
