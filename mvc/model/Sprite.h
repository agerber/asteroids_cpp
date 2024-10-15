#ifndef SPRITE_H
#define SPRITE_H



#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Movable.h"
#include "PolarPoint.h"

class CommandCenter;
class Game;

class Sprite : public Movable {
public:
    Sprite();

    void setCenter(sf::Vector2f center);
    sf::Vector2f getCenter() const override;

    void setDeltaX(double deltaX);
    double getDeltaX() const;

    void setDeltaY(double deltaY);
    double getDeltaY() const;

    void setTeam(Movable::Team);
    Movable::Team getTeam() const override;

    void setRadius(int radius);
    int getRadius() const override;

    void setOrientation(int orientation);
    int getOrientation();

    void setExpiry(int expiry);
    int getExpiry() const;

    void setSpin(int spin);
    int getSpin() const;

    void setCartesians(const std::vector<sf::Vector2f>& points);
    std::vector<sf::Vector2f> getCartesians();

    void setColor(sf::Color color);
    sf::Color getColor() const;

    void setRasterMap(const std::map<int, sf::Texture>& map);
    const std::map<int, sf::Texture>& getRasterMap() const;

    void move() override;
    bool isProtected() const override;

    static sf::Texture loadGraphic(const std::string& imagePath);
    void renderRaster(sf::RenderTarget& target, const sf::Texture& texture) const;
    void renderRaster(sf::RenderTarget& target, const sf::Texture& texture, int diam) const;
    void renderVector(sf::RenderTarget& target) const;

protected:
    int somePosNegValue(int seed);

    void expire();

private:
    sf::Vector2f center;
    double deltaX, deltaY;
    Movable::Team team;
    int radius, orientation, expiry, spin;
    std::vector<sf::Vector2f> cartesians;
    sf::Color color;
    std::map<int, sf::Texture> rasterMap;
};
/**
#include <QObject>
#include <QPoint>
#include <QMap>
#include <QString>
#include <QPainter>
#include <QColor>
#include <QVector>
#include "Movable.h"

class CommandCenter;
class Game;

class Sprite : public Movable
{
    Q_OBJECT
public:
    Sprite(QObject *parent = nullptr);

    void setCenter(QPoint center);
    QPoint getCenter() override;

    void setDeltaX(double deltaX);
    double getDeltaX() const;

    void setDeltaY(double deltaY);
    double getDeltaY() const;

    void setTeam(Movable::Team );
    Movable::Team getTeam() override;

    void setRadius(int radius);
    int getRadius() override;

    void setOrientation(int orientation);
    int getOrientation() ;

    void setExpiry(int expiry);
    int getExpiry() const;

    void setSpin(int spin);
    int getSpin() const;

    void setCartesians(QVector<QPoint> points);
    QVector<QPoint> getCartesians() ;

    void setColor(QColor color);
    QColor getColor() ;

    void setRasterMap(QMap<int, QImage>& map);
    QMap<int, QImage>& getRasterMap() ;

    virtual void move();
    virtual bool isProtected();

    static QImage loadGraphic(QString imagePath);
    void renderRaster(QPainter &painter, QImage image);
    void renderRaster(QPainter &painter, QImage image, int diam);
    void renderVector(QPainter &painter);

protected:
    int somePosNegValue(int seed);

    void expire();

private:
    QPoint center;
    double deltaX, deltaY;
    Movable::Team team;
    int radius, orientation, expiry, spin;
    QVector<QPoint> cartesians;
    QColor color;
    QMap<int, QImage> rasterMap;

signals:

};
**/

#endif // SPRITE_H
