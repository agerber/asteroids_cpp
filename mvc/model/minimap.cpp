#include "minimap.h"
#include "CommandCenter.h"
#include "Game.h"
#include "Asteroid.h"
#include "Nuke.h"

const sf::Color DARK_GRAY(64, 64, 64);

void MiniMap::draw(sf::RenderWindow &window)
{
    if (!CommandCenter::getInstance()->isRadar()) return;
    
    // Get the aspect ratio to adjust for non-square universes
    aspectRatio = aspectAdjustedRatio(CommandCenter::getInstance()->getUniDim());

    int miniWidth = static_cast<int>(MINI_MAP_PERCENT * Game::DIM.x * aspectRatio.getWidth());
    int miniHeight = static_cast<int>(MINI_MAP_PERCENT * Game::DIM.y * aspectRatio.getHeight());

    // Draw the bounding box (entire universe)
    sf::RectangleShape boundingBox(sf::Vector2f(miniWidth, miniHeight));
    boundingBox.setOutlineColor(DARK_GRAY);
    boundingBox.setOutlineThickness(1);
    boundingBox.setFillColor(sf::Color::Transparent);
    window.draw(boundingBox);

    // Draw the view-portal box
    sf::RectangleShape viewPortBox(sf::Vector2f(
        miniWidth / CommandCenter::getInstance()->getUniDim().x,
        miniHeight / CommandCenter::getInstance()->getUniDim().y));
    viewPortBox.setOutlineColor(DARK_GRAY);
    viewPortBox.setOutlineThickness(1);
    viewPortBox.setFillColor(sf::Color::Transparent);
    window.draw(viewPortBox);

    // Draw debris radar-blips
    for (const auto& mov : CommandCenter::getInstance()->getMovDebris()) {
        sf::CircleShape blip(1);
        blip.setPosition(translatePoint(mov->getCenter()));
        blip.setFillColor(DARK_GRAY);
        window.draw(blip);
    }

    // Draw foe (asteroid) radar-blips
    for (const auto& mov : CommandCenter::getInstance()->getMovFoes()) {
        if (auto asteroid = dynamic_cast<Asteroid*>(mov.get())) {
            sf::Vector2f translatedPoint = translatePoint(asteroid->getCenter());
            if (asteroid->getSize() == 0) {
                sf::CircleShape largeBlip(3);
                largeBlip.setPosition(translatedPoint);
                largeBlip.setFillColor(LIGHT_GRAY);
                window.draw(largeBlip);
            } else if (asteroid->getSize() == 1) {
                sf::CircleShape mediumBlip(3);
                mediumBlip.setPosition(translatedPoint);
                mediumBlip.setOutlineColor(LIGHT_GRAY);
                mediumBlip.setOutlineThickness(1);
                mediumBlip.setFillColor(sf::Color::Transparent);
                window.draw(mediumBlip);
            } else {
                sf::CircleShape smallBlip(2);
                smallBlip.setPosition(translatedPoint);
                smallBlip.setOutlineColor(LIGHT_GRAY);
                smallBlip.setOutlineThickness(1);
                smallBlip.setFillColor(sf::Color::Transparent);
                window.draw(smallBlip);
            }
        }
    }

    // Draw floater radar-blips
    for (const auto& mov : CommandCenter::getInstance()->getMovFloaters()) {
        sf::RectangleShape blip(sf::Vector2f(4, 4));
        blip.setPosition(translatePoint(mov->getCenter()));
        blip.setFillColor(dynamic_cast<NukeFloater*>(mov.get()) ? sf::Color::Yellow : sf::Color::Cyan);
        window.draw(blip);
    }

    // Draw friend radar-blips
    for (const auto& mov : CommandCenter::getInstance()->getMovFriends()) {
        sf::Color color;
        if (dynamic_cast<Falcon*>(mov.get()) && CommandCenter::getInstance()->getFalcon()->getShield() > 0)
            color = sf::Color::Cyan;
        else if (dynamic_cast<Nuke*>(mov.get()))
            color = sf::Color::Yellow;
        else
            color = PUMPKIN;

        sf::CircleShape blip(2);
        blip.setPosition(translatePoint(mov->getCenter()));
        blip.setFillColor(color);
        window.draw(blip);
    }
    std::cout << "MiniMap::draw" << std::endl;
}

sf::Vector2f MiniMap::translatePoint(const sf::Vector2f &point) const
{
    return sf::Vector2f(
        static_cast<float>(MINI_MAP_PERCENT * point.x / CommandCenter::getInstance()->getUniDim().x * aspectRatio.getWidth()),
        static_cast<float>(MINI_MAP_PERCENT * point.y / CommandCenter::getInstance()->getUniDim().y * aspectRatio.getHeight())
        );
}

AspectRatio MiniMap::aspectAdjustedRatio(const sf::Vector2u &universeDim) const
{
    if (universeDim.x == universeDim.y) {
        return AspectRatio(1.0, 1.0);
    } else if (universeDim.x > universeDim.y) {
        double wMultiple = static_cast<double>(universeDim.x) / universeDim.y;
        return AspectRatio(wMultiple, 1.0).scale(0.5);
    } else {
        double hMultiple = static_cast<double>(universeDim.y) / universeDim.x;
        return AspectRatio(1.0, hMultiple).scale(0.5);
    }
}
