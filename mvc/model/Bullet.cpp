#include "Bullet.h"
#include "Utils.h"
#include <cmath>

Bullet::Bullet(Falcon* falcon) : Sprite() {
    setTeam(Movable::FRIEND);
    setColor(sf::Color::Yellow);
    setExpiry(20);
    setRadius(6);

    setCenter(falcon->getCenter());
    setOrientation(falcon->getOrientation());

    const double FIRE_POWER = 35.0;
    double vectorX = std::cos(Utils::my_qDegreesToRadians(getOrientation())) * FIRE_POWER;
    double vectorY = std::sin(Utils::my_qDegreesToRadians(getOrientation())) * FIRE_POWER;

    setDeltaX(falcon->getDeltaX() + vectorX);
    setDeltaY(falcon->getDeltaY() + vectorY);

    const double KICK_BACK_DIVISOR = 36.0;
    falcon->setDeltaX(falcon->getDeltaX() - vectorX / KICK_BACK_DIVISOR);
    falcon->setDeltaY(falcon->getDeltaY() - vectorY / KICK_BACK_DIVISOR);

    std::vector<sf::Vector2f> listPoints{
        sf::Vector2f(0, 3),
        sf::Vector2f(1, -1),
        sf::Vector2f(0, 0),
        sf::Vector2f(-1, -1)
    };

    setCartesians(listPoints);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    renderVector(target);
}



/**
#include <QColor>
#include <QVector>
#include <cmath>

#include "Bullet.h"
#include "Falcon.h"
#include "Utils.h"

Bullet::Bullet(Falcon* falcon):
    Sprite()
{
    //Movable::FRIEND, QColor(Qt::GlobalColor::yellow)
    setTeam(Movable::FRIEND);
    setColor(Qt::GlobalColor::yellow); //to change Origin
    //a bullet expires after 20 frames.
    setExpiry(20);
    setRadius(6);

    //everything is relative to the falcon ship that fired the bullet
    setCenter(falcon->getCenter());

    //set the bullet orientation to the falcon (ship) orientation
    setOrientation(falcon->getOrientation());

    const double FIRE_POWER = 35.0;
    double vectorX =
            std::cos(Utils::my_qDegreesToRadians(getOrientation())) * FIRE_POWER;
    double vectorY =
            std::sin(Utils::my_qDegreesToRadians(getOrientation())) * FIRE_POWER;

    //fire force: falcon inertia + fire-vector
    setDeltaX(falcon->getDeltaX() + vectorX);
    setDeltaY(falcon->getDeltaY() + vectorY);

    //we have a reference to the falcon passed into the constructor. Let's create some kick-back.
    //fire kick-back on the falcon: inertia - fire-vector / some arbitrary divisor
    const double KICK_BACK_DIVISOR = 36.0;
    falcon->setDeltaX(falcon->getDeltaX() - vectorX / KICK_BACK_DIVISOR);
    falcon->setDeltaY(falcon->getDeltaY() - vectorY / KICK_BACK_DIVISOR);

    //define the points on a cartesian grid
    QVector<QPoint> listPoints = QVector<QPoint>{
        QPoint(0, 3), //top point
        QPoint(1, -1), //right bottom
        QPoint(0, 0),
        QPoint(-1, -1) //left bottom
    };

    setCartesians(listPoints);
}

void Bullet::draw(QPainter& painter)
{
    renderVector(painter);
}
**/
