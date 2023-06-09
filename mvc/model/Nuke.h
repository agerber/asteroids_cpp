#ifndef NUKE_H
#define NUKE_H

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

#endif // 