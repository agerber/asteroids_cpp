#ifndef FLOATER_H
#define FLOATER_H

#include <QPainter>
#include "Sprite.h"

class Floater : public Sprite {
public:
    Floater();

    void draw(QPainter &painter) override;
};

#endif // FLOATER_H