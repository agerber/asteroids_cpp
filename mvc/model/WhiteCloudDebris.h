#ifndef WHITECLOUDDEBRIS_H
#define WHITECLOUDDEBRIS_H

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

#endif // WHITECLOUDDEBRIS_H
