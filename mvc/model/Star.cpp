
#include "Star.h"

Star::Star(float x, float y) {
    starShape.setPosition(x, y);
    starShape.setRadius(5.f);
    starShape.setFillColor(sf::Color::White);
}

void Star::draw(sf::RenderWindow &window) {
    window.draw(starShape);
}

