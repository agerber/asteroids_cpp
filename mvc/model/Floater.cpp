#include "Floater.h"
#include "CommandCenter.h"
#include "utils.h"

#include <QPoint>

Floater::Floater() : Sprite() {
    setTeam(Team::FLOATER);

    setExpiry(250);
    setColor(Qt::white);
    setRadius(50);
    setDeltaX(somePosNegValue(10));
    setDeltaY(somePosNegValue(10));
    setSpin(somePosNegValue(10));

    QVector<QPoint> points;
    points << QPoint(5, 5)
           << QPoint(4, 0)
           << QPoint(5, -5)
           << QPoint(0, -4)
           << QPoint(-5, -5)
           << QPoint(-4, 0)
           << QPoint(-5, 5)
           << QPoint(0, 4);
    setCartesians(points);
}

void Floater::draw(QPainter &painter) {
    renderVector(painter);
}