#ifndef MOVABLE_H
#define MOVABLE_H


#include <SFML/Graphics.hpp>

class Movable {
public:
    enum Team { FRIEND, FOE, FLOATER, DEBRIS };

    Movable();
    virtual ~Movable() = default;

    virtual void move() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual sf::Vector2f getCenter() const = 0;
    virtual int getRadius() const = 0;
    virtual Movable::Team getTeam() const = 0;
    virtual bool isProtected() const = 0;
};
/**
#include <QPoint>
#include <QPainter>
#include <QObject>

class Movable : public QObject{
    Q_OBJECT
public:
    enum Team {FRIEND, FOE, FLOATER, DEBRIS};
    Movable();
    Movable(QObject *parent);
    ~Movable() {};
    virtual void move() = 0;
    virtual void draw(QPainter &painter)  = 0;
    virtual QPoint getCenter()  = 0;
    virtual int getRadius() = 0;
    virtual Movable::Team getTeam()  = 0;
    virtual bool isProtected()  = 0;
};
**/

#endif // MOVABLE_H



