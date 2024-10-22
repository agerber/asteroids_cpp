#include "Sprite.h"
#include "Game.h"
#include <memory>

Sprite::Sprite()
{
    center = sf::Vector2f(Game::nextInt(Game::DIM.x),
                          Game::nextInt(Game::DIM.y));
}

void Sprite::move()
{
    // Right-bounds reached
    if (center.x > Game::DIM.x) {
        center.x = 1;
    } else if (center.x < 0) { // Left-bounds reached
        center.x = Game::DIM.x - 1;
    } else if (center.y > Game::DIM.y) { // Bottom-bounds reached
        center.y = 1;
    } else if (center.y < 0) { // Top-bounds reached
        center.y = Game::DIM.y - 1;
    } else {
        center.x += deltaX;
        center.y += deltaY;
    }

    // Expire on short-lived objects only
    if (expiry > 0) expire();

    // Adjust orientation for spinning objects
    if (spin != 0) orientation += spin;
}

int Sprite::somePosNegValue(int seed)
{
    int randomNumber = Game::nextInt(seed);
    return (randomNumber % 2 == 0) ? randomNumber : -randomNumber;
}

void Sprite::renderVector(sf::RenderWindow &window)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(cartesians.size());

    // Adjust cartesians for location and apply transformations
    for (size_t i = 0; i < cartesians.size(); ++i) {
        float x = cartesians[i].x * radius * std::sin(orientation * (3.14159 / 180)) + center.x;
        float y = cartesians[i].y * radius * std::cos(orientation * (3.14159 / 180)) + center.y;
        polygon.setPoint(i, sf::Vector2f(x, y));
    }

    polygon.setFillColor(color);
    window.draw(polygon);
}

std::shared_ptr<sf::Texture> Sprite::loadGraphic(const std::string &imagePath)
{
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(imagePath)) {
        std::cerr << "Error loading image: " << imagePath << std::endl;
        return nullptr;
    }
    return texture;
}

void Sprite::renderRaster(sf::RenderWindow &window, const std::shared_ptr<sf::Texture> &texture)
{
    int diam = getRadius() * 2;
    renderRaster(window, texture, diam);
}

void Sprite::renderRaster(sf::RenderWindow &window, const std::shared_ptr<sf::Texture> &texture, int diam)
{
    if (!texture || texture->getSize().x == 0 || texture->getSize().y == 0) return;

    sf::Sprite sprite;
    sprite.setTexture(*texture);

    // Calculate scale based on desired diameter
    float scaleX = static_cast<float>(diam) / texture->getSize().x;
    float scaleY = static_cast<float>(diam) / texture->getSize().y;
    sprite.setScale(scaleX, scaleY);

    // Set the sprite's origin to the center of the image (for correct rotation and translation)
    sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);

    // Set position to the center point
    sprite.setPosition(center);

    sprite.setRotation(orientation);

    // Draw the sprite
    window.draw(sprite);
}

void Sprite::expire()
{
    if (expiry == 1) {
        CommandCenter::getInstance()->getOpsQueue().enqueue(shared_from_this(), GameOp::Action::REMOVE);
    }
    expiry--;
}
