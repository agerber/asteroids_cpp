#ifndef STAR_H
#define STAR_H



#include <SFML/Graphics.hpp>
#include "Movable.h"

class Star : public Movable {
public:
    Star();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f getCenter() const override;
    int getRadius() const override;
    Movable::Team getTeam() const override;
    bool isProtected() const override;
    void move() override;

private:
    sf::Vector2f center;
    sf::Color color;
};


/**
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
**/

#endif // STA
