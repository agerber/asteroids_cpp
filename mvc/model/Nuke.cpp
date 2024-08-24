#include "Nuke.h"

#include <cmath>
#include <QPainter>

#include "Utils.h"

Nuke::Nuke(Falcon *falcon) {
    setCenter(falcon->getCenter());
    setColor(Qt::yellow);
    setExpiry(EXPIRE);
    setRadius(0);
    setTeam(Team::FRIEND);

    const double FIRE_POWER = 11.0;
    double vectorX =
            std::cos(Utils::my_qDegreesToRadians((float)falcon->getOrientation())) * FIRE_POWER;
    double vectorY =
            std::sin(Utils::my_qDegreesToRadians(falcon->getOrientation())) * FIRE_POWER;

    //fire force: falcon inertia + fire-vector
    setDeltaX(falcon->getDeltaX() + vectorX);
    setDeltaY(falcon->getDeltaY() + vectorY);

}

void Nuke::draw(QPainter &painter) {
    painter.setPen(getColor());
    painter.drawEllipse(getCenter().x() - getRadius(), getCenter().y() - getRadius(), getRadius() * 2, getRadius() * 2);
}

bool Nuke::isProtected() {
    return true;
}

void Nuke::move() {
    Sprite::move();
    if (getExpiry() % (EXPIRE / 6) == 0) nukeState++;
    switch (nukeState) {
        //travelling
        case 0:
            setRadius(2);
            break;
        //exploding
        case 1:
        case 2:
        case 3:
            setRadius(getRadius() + 16);
            break;
        //imploding
        case 4:
        case 5:
        default:
            setRadius(getRadius() - 22);
            break;


    }
}
