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


