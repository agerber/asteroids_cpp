#ifndef BRICK_H
#define BRICK_H

#include <QPoint>
#include <QImage>
#include <map>
#include <Sprite.h>

class Brick : public Sprite {

private:
    const int BRICK_IMAGE = 0;

public:
    //The size of this brick is always square!
    //we use upperLeftCorner because that is the origin when drawing graphics in Java
    Brick(QPoint upperLeftCorner, int size);

    void draw(QPainter &painter) override;

    //the reason we override the move method is to skip the logic contained in super-class Sprite move() method
    //which is laborious, thereby gaining slight performance
    void move();
};


#endif // BRICK_H
