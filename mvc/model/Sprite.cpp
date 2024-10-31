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

    // 1: Convert raw cartesians to raw polars
    std::vector<PolarPoint> polars = Utils::cartesianToPolar(cartesians);

    // 2: Rotate raw polars given the orientation of the sprite
    auto rotatePolarByOrientation = [&](const PolarPoint& pp) -> PolarPoint
    {
        float adjustedTheta = pp.getTheta() + Utils::my_qDegreesToRadians(-orientation - 90); // Rotated theta
        return PolarPoint(pp.getR(), adjustedTheta);
    };

    // 3: Convert the rotated polars back to cartesians (apply radius scaling correctly)
    auto polarToCartesian = [&](const PolarPoint& pp) -> sf::Vector2f
    {
        // Adjust the scaling to match the original proportions
        float x = pp.getR() * std::cos(pp.getTheta());
        float y = pp.getR() * std::sin(pp.getTheta());
        return sf::Vector2f(x, y);
    };

    // 4: Adjust for the sprite's location (center point)
    auto adjustForLocation = [&](const sf::Vector2f& p) -> sf::Vector2f
    {
        return sf::Vector2f(center.x + (p.x * radius), center.y - (p.y * radius));
    };

    // 5: Apply the transformations and set the points on the polygon
    std::vector<sf::Vector2f> points;
    for (const auto& pp : polars) {
        PolarPoint rotated = rotatePolarByOrientation(pp);
        sf::Vector2f cartesian = polarToCartesian(rotated);
        sf::Vector2f finalPosition = adjustForLocation(cartesian);
        points.push_back(finalPosition);
    }

    for (size_t i = 0; i < points.size(); ++i) {
        polygon.setPoint(i, points[i]);
    }

    // Set the fill color
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setOutlineColor(color);
    polygon.setOutlineThickness(1.0f);

    // Draw the polygon
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
