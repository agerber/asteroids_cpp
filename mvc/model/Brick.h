#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include <map>

class Brick : public sf::Drawable {
private:
    const int BRICK_IMAGE = 0;

public:
    Brick(sf::Vector2f upperLeftCorner, int size);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void move();
};



#endif // BRICK_H
