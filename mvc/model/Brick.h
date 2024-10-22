#ifndef BRICK_H
#define BRICK_H

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <map>
#include <memory>


class Brick: public Sprite {
private:
    const int BRICK_IMAGE = 0;

public:
    Brick(sf::Vector2f upperLeftCorner, int size) {
        // Set the team to FOE
        setTeam(Team::FOE);

        // Center point and radius calculation
        setCenter(sf::Vector2f(upperLeftCorner.x + size / 2, upperLeftCorner.y + size / 2));
        setRadius(size / 2);

        // Load the brick image and add it to the raster map
        std::map<int, std::shared_ptr<sf::Texture>> rasterMap;
        auto texture = std::make_shared<sf::Texture>();
        if (texture->loadFromFile("resources/imgs/brick/Brick_Block100.png")) {
            rasterMap[BRICK_IMAGE] = texture;
        } else {
            std::cerr << "Error: Unable to load image: imgs/brick/Brick_Block100.png" << std::endl;
        }

        setRasterMap(rasterMap);
    }

    // Overriding draw method to render the brick
    void draw(sf::RenderWindow& window) override {
        auto texture = getRasterMap().at(BRICK_IMAGE);
        if (texture) {
            sf::Sprite sprite;
            sprite.setTexture(*texture);
            auto center = getCenter();
            sprite.setPosition(center.x - getRadius(), center.y - getRadius());
            window.draw(sprite);
        }
        // Uncomment these to visualize collision
        // sf::CircleShape circle(getRadius());
        // circle.setPosition(getCenter().x - getRadius(), getCenter().y - getRadius());
        // circle.setFillColor(sf::Color::Transparent);
        // circle.setOutlineColor(sf::Color::LightGray);
        // circle.setOutlineThickness(1);
        // window.draw(circle);
    }

    // Overriding move method - bricks do not move
    void move() override {
        // No movement logic for bricks
    }
};

#endif
