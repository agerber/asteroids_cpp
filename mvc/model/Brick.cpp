#include "Brick.h"


Brick::Brick(sf::Vector2f upperLeftCorner, int size)
{
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

void Brick::draw(sf::RenderWindow &window)
{
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

void Brick::move()
{
    //bricks dont move
}
