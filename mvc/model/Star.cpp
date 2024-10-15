#include "Star.h"
#include "Game.h"
#include <cstdlib>  // for rand()

Star::Star() :
    center(static_cast<float>(rand() % Game::DIM.x),
             static_cast<float>(rand() % Game::DIM.y))
{
    int bright = rand() % 226;  // Brightness between 0 and 225
    color = sf::Color(bright, bright, bright);  // Some grey value
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::CircleShape starShape(getRadius());
    starShape.setFillColor(color);
    starShape.setPosition(center.x - getRadius(), center.y - getRadius());
    target.draw(starShape, states);
}

sf::Vector2f Star::getCenter() const {
    return center;
}

int Star::getRadius() const {
    return 1;
}

Movable::Team Star::getTeam() const {
    return DEBRIS;
}

bool Star::isProtected() const {
    return false;
}

void Star::move() {
    // Do nothing
}


/**
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
**/
