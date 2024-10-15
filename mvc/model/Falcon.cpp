#include "Falcon.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

Falcon::Falcon() : Sprite() {
    setTeam(FRIEND);
    setRadius(MIN_RADIUS);
    setThrusting(false);

    sf::Texture texture;
    texture.loadFromFile("resources/imgs/fal/falcon125.png");
    rasterMap[FALCON] = texture;

    texture.loadFromFile("resources/imgs/fal/falcon125_thr.png");
    rasterMap[FALCON_THR] = texture;

    texture.loadFromFile("resources/imgs/fal/falcon125_PRO.png");
    rasterMap[FALCON_PRO] = texture;

    texture.loadFromFile("resources/imgs/fal/falcon125_PRO_thr.png");
    rasterMap[FALCON_PRO_THR] = texture;
}

bool Falcon::isProtected() const {
    return shield > 0;
}

void Falcon::move() {
    Sprite::move();

    if (invisible > 0) invisible--;
    if (shield > 0) shield--;
    if (nukeMeter > 0) nukeMeter--;
    if (showLevel > 0) showLevel--;

    const double THRUST = 0.85;
    const int MAX_VELOCITY = 39;

    if (thrusting) {
        double vectorX = std::cos(Utils::my_qDegreesToRadians(getOrientation())) * THRUST;
        double vectorY = std::sin(Utils::my_qDegreesToRadians(getOrientation())) * THRUST;

        int absVelocity = static_cast<int>(
            std::sqrt(std::pow(getDeltaX() + vectorX, 2) + std::pow(getDeltaY() + vectorY, 2))
            );

        if (absVelocity < MAX_VELOCITY) {
            setDeltaX(getDeltaX() + vectorX);
            setDeltaY(getDeltaY() + vectorY);
            setRadius(MIN_RADIUS + absVelocity / 3);
            maxSpeedAttained = false;
        } else {
            maxSpeedAttained = true;
        }
    }

    int adjustOr = getOrientation();
    switch (turnState) {
    case LEFT:
        adjustOr = getOrientation() <= 0 ? 360 - TURN_STEP : getOrientation() - TURN_STEP;
        break;
    case RIGHT:
        adjustOr = getOrientation() >= 360 ? TURN_STEP : getOrientation() + TURN_STEP;
        break;
    case IDLE:
    default:
        break;
    }
    setOrientation(adjustOr);
}

void Falcon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    ImageState imageState;
    if (invisible > 0) {
        imageState = FALCON_INVISIBLE;
    } else if (isProtected()) {
        imageState = thrusting ? FALCON_PRO_THR : FALCON_PRO;
        drawShield(target);
    } else {
        imageState = thrusting ? FALCON_THR : FALCON;
    }

    if (rasterMap.find(imageState) != rasterMap.end()) {
        sf::Sprite sprite(rasterMap.at(imageState));
        sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
        sprite.setPosition(getCenter());
        sprite.setScale(getRadius() * 4 / sprite.getLocalBounds().width, getRadius() * 4 / sprite.getLocalBounds().height);
        target.draw(sprite, states);
    }
}

void Falcon::drawShield(sf::RenderTarget& target) const {
    sf::CircleShape shieldShape(getRadius() * 2);
    shieldShape.setOrigin(getRadius() * 2, getRadius() * 2);
    shieldShape.setPosition(getCenter());
    shieldShape.setOutlineColor(sf::Color::Cyan);
    shieldShape.setOutlineThickness(1.0f);
    shieldShape.setFillColor(sf::Color::Transparent);
    target.draw(shieldShape);
}

void Falcon::setShield(int shield_in) { shield = shield_in; }
int Falcon::getShield() { return shield; }

void Falcon::setNukeMeter(int nukeMeter_in) { nukeMeter = nukeMeter_in; }
int Falcon::getNukeMeter() { return nukeMeter; }

void Falcon::setInvisible(int invisible_in) { invisible = invisible_in; }
int Falcon::getInvisible() { return invisible; }

void Falcon::setMaxSpeedAttained(int maxSpeedAttained_in) { maxSpeedAttained = maxSpeedAttained_in; }
bool Falcon::getMaxSpeedAttained() { return maxSpeedAttained; }

void Falcon::setShowLevel(int showLevel_in) { showLevel = showLevel_in; }
int Falcon::getShowLevel() { return showLevel; }

void Falcon::setThrusting(bool thrusting_in) { thrusting = thrusting_in; }
bool Falcon::getThrusting() { return thrusting; }

void Falcon::setTurnState(TurnState w_state) { turnState = w_state; }
Falcon::TurnState Falcon::getTurnState() { return turnState; }


/**
#include "Falcon.h"
#include "GamePanel.h"

#include <QPainter>
#include <QColor>
#include <QtMath>

#include "Utils.h"

#include <string>
#include <iostream>

using namespace std;

// ==============================================================
// CONSTRUCTOR
// ==============================================================
Falcon::Falcon() : Sprite()
{
    setTeam(FRIEND);
    setRadius(MIN_RADIUS);
    setThrusting(false);

    //We use QMap which has a seek-time of O(1)
    //See the resources directory in the root of this project for pngs.
    //Using enums as keys is safer b/c we know the value exists when we reference the consts later in code.
    rasterMap.insert(FALCON_INVISIBLE, QImage()); //null image
    rasterMap.insert(FALCON, QImage(":/resources/imgs/fal/falcon125.png")); //normal ship
    rasterMap.insert(FALCON_THR, QImage(":/resources/imgs/fal/falcon125_thr.png")); //normal ship thrusting
    rasterMap.insert(FALCON_PRO, QImage(":/resources/imgs/fal/falcon125_PRO.png")); //protected ship (green)
    rasterMap.insert(FALCON_PRO_THR, QImage(":/resources/imgs/fal/falcon125_PRO_thr.png")); //green thrusting
}



bool Falcon::isProtected()
{
    return  shield > 0;
}

void Falcon::move()
{
    Sprite::move();

    if (invisible > 0) invisible--;
    if (shield > 0) shield--;
    if (nukeMeter > 0) nukeMeter--;
    //The falcon is a convenient place to decrement the showLevel variable as the falcon
    //move() method is being called every frame (~40ms); and the falcon reference is never null.
    if (showLevel > 0) showLevel--;

    const double THRUST = 0.85;
    const int MAX_VELOCITY = 39;


    //apply some thrust vectors using trig.
    if (thrusting) {
        double vectorX = qCos(Utils::my_qDegreesToRadians(getOrientation())) * THRUST;
        double vectorY = qSin(Utils::my_qDegreesToRadians(getOrientation())) * THRUST;

        //Absolute velocity is the hypotenuse of deltaX and deltaY
        int absVelocity = (int)qSqrt(qPow(getDeltaX() + vectorX, 2) + qPow(getDeltaY() + vectorY, 2));

        //only accelerate (or adjust radius) if we are below the maximum absVelocity.
        if (absVelocity < MAX_VELOCITY){
            //accelerate
            setDeltaX(getDeltaX() + vectorX);
            setDeltaY(getDeltaY() + vectorY);
            //Make the ship radius bigger when the absolute velocity increases, thereby increasing difficulty when not
            // protected, and allowing player to use the shield offensively when protected.
            setRadius(MIN_RADIUS + absVelocity / 3);
            maxSpeedAttained = false;
        } else {
            //at max speed, you will lose steerage if you attempt to accelerate in the same general direction
            //show WARNING message to player using this flag (see drawFalconStatus() of GamePanel class)
            maxSpeedAttained = true;
        }

    }

    //adjust the orientation given turnState
    int adjustOr = getOrientation();
    switch (turnState){
        case LEFT:
            adjustOr = getOrientation() <= 0 ? 360 - TURN_STEP : getOrientation() - TURN_STEP;
            break;
        case RIGHT:
            adjustOr = getOrientation() >= 360 ? TURN_STEP : getOrientation() + TURN_STEP;
            break;
        case IDLE:
        default:
            //do nothing
            break;
    }
    setOrientation(adjustOr);

//    cout << getOrientation();
//    cout << ":";

}

void Falcon::draw(QPainter &painter)
{
    //set local image-state
    ImageState imageState;
    if (invisible > 0){
        imageState = FALCON_INVISIBLE;
    }
    else if (isProtected()){
        imageState = thrusting ? FALCON_PRO_THR : FALCON_PRO;
        //you can also combine vector elements and raster elements
        drawShield(painter);
    }
    else { //not protected
        imageState = thrusting ? FALCON_THR : FALCON;
    }

    //Render the raster image according to the image-state
    Sprite::renderRaster(painter, rasterMap.value(imageState), getRadius() * 4);
}

void Falcon::drawShield(QPainter &painter)
{
    painter.setPen(Qt::cyan);
    painter.drawEllipse(getCenter(), getRadius()*2,getRadius()*2);
}

**/
