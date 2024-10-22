#include "Bullet.h"
#include "utils.h"

Bullet::Bullet(const Falcon &falcon)
{
    // Set as a friendly unit
    setTeam(Team::FRIEND);
    setColor(sf::Color(255,215,0));

    // Bullet expires after 20 frames
    setExpiry(20);
    setRadius(6);

    // Position is relative to the Falcon's position
    setCenter(falcon.getCenter());

    // Set bullet orientation to Falcon's orientation
    setOrientation(falcon.getOrientation());

    const double FIRE_POWER = 35.0;
    double vectorX = std::cos( Utils::my_qDegreesToRadians(getOrientation() ) ) * FIRE_POWER;
    double vectorY = std::sin( Utils::my_qDegreesToRadians(getOrientation() ) ) * FIRE_POWER;

    // Fire force: Falcon inertia + fire-vector
    setDeltaX(falcon.getDeltaX() + vectorX);
    setDeltaY(falcon.getDeltaY() + vectorY);

    // Apply kick-back to the Falcon
    const double KICK_BACK_DIVISOR = 36.0;
    Falcon& mutableFalcon = const_cast<Falcon&>(falcon);
    mutableFalcon.setDeltaX(falcon.getDeltaX() - vectorX / KICK_BACK_DIVISOR);
    mutableFalcon.setDeltaY(falcon.getDeltaY() - vectorY / KICK_BACK_DIVISOR);

    // Define the points on a cartesian grid
    std::vector<sf::Vector2f> listPoints = {
        sf::Vector2f(0, 3),   // Top point
        sf::Vector2f(1, -1),  // Right bottom
        sf::Vector2f(0, 0),   // Center
        sf::Vector2f(-1, -1)  // Left bottom
    };

    setCartesians(listPoints);
}

void Bullet::draw(sf::RenderWindow &window)
{
    renderVector(window);
}
