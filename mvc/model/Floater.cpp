#include "Floater.h"


Floater::Floater()
{
    // Set the team to FLOATER
    setTeam(Team::FLOATER);

    // Default values, which can be overridden in the concrete classes
    setExpiry(250);
    setColor(sf::Color::White);
    setRadius(50);

    // Set random DeltaX, DeltaY, and spin
    setDeltaX(somePosNegValue(10));
    setDeltaY(somePosNegValue(10));
    setSpin(somePosNegValue(10));

    // Cartesian points defining the shape of the polygon
    std::vector<sf::Vector2f> listPoints = {
        sf::Vector2f(5, 5),
        sf::Vector2f(4, 0),
        sf::Vector2f(5, -5),
        sf::Vector2f(0, -4),
        sf::Vector2f(-5, -5),
        sf::Vector2f(-4, 0),
        sf::Vector2f(-5, 5),
        sf::Vector2f(0, 4)
    };

    setCartesians(listPoints);
}

void Floater::draw(sf::RenderWindow &window)
{
    renderVector(window);
}
