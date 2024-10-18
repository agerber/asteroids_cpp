
#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>

class Star {
private:
    sf::CircleShape starShape;

public:
    Star(float x, float y);
    void draw(sf::RenderWindow &window);
};

#endif
