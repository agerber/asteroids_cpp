#include "Star.h"
#include "Game.h"

Star::Star() :
    center(rand() % Game::DIM.width(), rand() % Game::DIM.height())
{
    int bright = rand() % 226; //Stars are muted at max brightness of 225 out of 255
    color = QColor(bright, bright, bright); //some grey value
}

void Star::draw(QPainter& painter) {
    painter.setPen(color);
    painter.drawEllipse(center.x(), center.y(), getRadius(), getRadius());
}

QPoint Star::getCenter() {
    return center;
}

int Star::getRadius() {
    return 1;
}

Movable::Team Star::getTeam() {
    return DEBRIS;
}

bool Star::isProtected() {
    return false;
}

void Star::move() {
    // do nothing
}
