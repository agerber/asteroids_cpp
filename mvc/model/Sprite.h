#ifndef SPRITE_H
#define SPRITE_H

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

#endif // SPRITE_H
