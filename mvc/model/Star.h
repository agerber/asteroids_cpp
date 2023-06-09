#ifndef STAR_H
#define STAR_H

#include <QObject>
#include <QPoint>
#include <QColor>
#include <QPainter>

#include "Movable.h"

class Star : public Movable {
    Q_OBJECT

public:
    Star();
    void draw(QPainter& painter) override;
    QPoint getCenter() override;
    int getRadius() override;
    Movable::Team getTeam() override;
    bool isProtected() override;
    void move() override;

private:
    QPoint center;
    QColor color;
};

#endif // STA
