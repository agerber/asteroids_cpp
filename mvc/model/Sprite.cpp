#include "Sprite.h"
#include "CommandCenter.h"
#include "Game.h"
#include "Utils.h"
#include "Stream.h"

#include <QPainter>
#include <QTransform>
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>
#include <QtMath>

using namespace stream;
using namespace stream::op;

Sprite::Sprite(QObject *parent) : Movable(parent)
{
    spin = 0;
    deltaX = deltaY = 0;
    //team = Movable::FRIEND;
    radius = 0;
    orientation = 0;
    expiry = 0;
    //place the sprite at some random location in the game-space at instantiation
    setCenter(QPoint(rand() % Game::DIM.width(),
                      rand() % Game::DIM.height()));
}

void Sprite::setCenter(QPoint center)
{
    this->center = center;
}

QPoint Sprite::getCenter()
{
    return center;
}

void Sprite::setDeltaX(double deltaX)
{
    this->deltaX = deltaX;
}

double Sprite::getDeltaX() const
{
    return deltaX;
}

void Sprite::setDeltaY(double deltaY)
{
    this->deltaY = deltaY;
}

double Sprite::getDeltaY() const
{
    return deltaY;
}

void Sprite::setTeam(Movable::Team team_in)
{
    team = team_in;
}

Movable::Team Sprite::getTeam()
{
    return team;
}

void Sprite::setRadius(int radius)
{
    this->radius = radius;
}

int Sprite::getRadius()
{
    return radius;
}

void Sprite::setOrientation(int orientation)
{
    this->orientation = orientation;
}

int Sprite::getOrientation()
{
    return orientation;
}

void Sprite::setExpiry(int expiry)
{
    this->expiry = expiry;
}

int Sprite::getExpiry() const
{
    return expiry;
}

void Sprite::setSpin(int spin)
{
    this->spin = spin;
}

int Sprite::getSpin() const
{
    return spin;
}

void Sprite::setCartesians(QVector<QPoint> points)
{
    cartesians = points;
}

QVector<QPoint> Sprite::getCartesians() 
{
    return cartesians;
}

void Sprite::setColor(QColor color)
{
    this->color = color;
}

QColor Sprite::getColor() 
{
    return color;
}

void Sprite::setRasterMap(QMap<int, QImage>& map)
{
    rasterMap = map;
}

QMap<int, QImage>& Sprite::getRasterMap() 
{
    return rasterMap;
}

void Sprite::move()
{
    //The following code block just keeps the sprite inside the bounds of the frame.
    //To ensure this behavior among all sprites in your game, make sure to call super.move() in extending classes
    // where you need to override the move() method.

    //right-bounds reached
    if (center.x() > Game::DIM.width()) {
        setCenter(QPoint(1, center.y()));
    //left-bounds reached
    } else if (center.x() < 0) {
        setCenter(QPoint(Game::DIM.width() - 1, center.y()));
    //bottom-bounds reached
    } else if (center.y() > Game::DIM.height()) {
        setCenter(QPoint(center.x(), 1));
    //top-bounds reached
    } else if (center.y() < 0) {
        setCenter(QPoint(center.x(), Game::DIM.height() - 1));
    //in-bounds
    } else {
        double newXPos = center.x() + getDeltaX();
        double newYPos = center.y() + getDeltaY();
        setCenter(QPoint((int) newXPos, (int) newYPos));
    }

    //expire (decrement expiry) on short-lived objects only
    //the default value of expiry is zero, so this block will only apply to expiring sprites
    if (expiry > 0) expire();

    //if a sprite spins, adjust its orientation
    //the default value of spin is zero, therefore non-spinning objects will not call this block.
    if (spin != 0) {
        setOrientation(getOrientation() + spin);
    }
}

bool Sprite::isProtected()
{
    //by default, sprites are not protected
    return false;
}

QImage Sprite::loadGraphic(QString imagePath)
{
    QImage image(imagePath);
    if (image.isNull()) {
        qDebug() << "Error: couldn't load image at" << imagePath;
    }
    return image;
}
//overloaded
void Sprite::renderRaster(QPainter &painter, QImage image)
{
    int diam = getRadius() * 2;
    renderRaster(painter, image, diam);
}

//overloaded
void Sprite::renderRaster(QPainter &painter, QImage image, int diam)
{
    if (image.isNull()) return;

    int centerX = getCenter().x();
    int centerY = getCenter().y();
    int width = diam;
    int height = diam;
    double angleRadians = Utils::my_qDegreesToRadians(getOrientation());

    QTransform oldTransform = painter.worldTransform();
    QTransform transform(oldTransform);
    if (centerX != 0 || centerY != 0 ) {
        transform.translate(centerX, centerY);
    }
    double scaleX = width * 1.0 / image.width();
    double scaleY = height * 1.0 / image.height();
    transform.scale(scaleX, scaleY);
    if (angleRadians != 0) {
        transform.rotateRadians(angleRadians);
    }
    transform.translate(-image.width() / 2.0, -image.height() / 2.0);

    painter.setWorldTransform(transform);
    painter.drawImage(0, 0, image);
    painter.setWorldTransform(oldTransform);
}

void Sprite::renderVector(QPainter &painter)
{
    QPen pen;
    pen.setColor(color);
    painter.setPen(pen);

    // To render this Sprite in vector mode, we need to:
    // 1: convert raw cartesians to raw polars,
    // 2: rotate polars for orientation of sprite.
    // 3: Convert back to cartesians
    // 4: adjust for center-point (location).
    // and 5: pass the cartesian-x and cartesian-y coords as arrays along with length to painter.drawPolygon().

    // 1: convert raw cartesians to raw polars (used later in stream below)
    // The reason we convert cartesian-points to polar-points is that it's much easier to rotate polar-points
    QVector<PolarPoint> polars = Utils::cartesianToPolar(getCartesians());


    // 2: rotate raw polars given the orientation of the sprite.
    auto rotatePolarByOrientation = [&](const PolarPoint& pp) -> PolarPoint
    {
        return {pp.r, pp.theta + Utils::my_qDegreesToRadians(-orientation - 90)}; //rotated Theta
    };

    // 3: convert the rotated polars back to cartesians
    auto polarToCartesian = [&](const PolarPoint& pp) -> QPointF
    {
        return QPointF(pp.r * radius * cos(pp.theta), pp.r * radius * sin(pp.theta));
    };

    // 4: adjust the cartesians for the location (center-point) of the sprite.
    // the reason we subtract the y-value has to do with how Qt plots the vertical axis for
    // graphics (from top to bottom)
    auto adjustForLocation = [&](const QPointF& p) -> QPointF
    {
        return QPointF(center.x() + p.x(), center.y() - p.y());
    };

    // 5: draw the polygon using the List of raw polars from above, applying mapping transforms as required
    std::vector<QPointF> points = MakeStream::from(polars)
    | map_(rotatePolarByOrientation)
    | map_(polarToCartesian)
    | map_(adjustForLocation)
    | to_vector();

    painter.drawPolygon(points.data(), points.size());

}

int Sprite::somePosNegValue(int seed)
{
     int randomNumber = QRandomGenerator::global()->bounded(seed);
    return (randomNumber % 2 == 0) ? randomNumber : -randomNumber;

}

void Sprite::expire()
{
    if (expiry == 1) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(this, GameOp::REMOVE);
    }
    //and then decrements in all cases
    expiry--;
}


  