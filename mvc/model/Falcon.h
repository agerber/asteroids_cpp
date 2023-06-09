#ifndef FALCON_H
#define FALCON_H

#include "Sprite.h"
#include <QMap>
#include <QImage>

class Falcon : public Sprite
{
public:
    //images states
    enum ImageState {
        FALCON_INVISIBLE, //for pre-spawning
        FALCON, //normal ship
        FALCON_THR, //normal ship thrusting
        FALCON_PRO, //protected ship (green)
        FALCON_PRO_THR, //protected ship (green) thrusting
    };

    enum TurnState {IDLE, LEFT, RIGHT};

public:
    // ==============================================================
    // CONSTRUCTOR
    // ==============================================================
    Falcon();

    // ==============================================================
    // METHODS
    // ==============================================================
    void move() override;
    void draw(QPainter &painter) override;
    bool isProtected() override;
    void drawShield(QPainter &);

    void setShield(int shield_in) { shield = shield_in; };
    int  getShield() { return shield; }

    void setNukeMeter(int nukeMeter_in) { nukeMeter = nukeMeter_in; };
    int getNukeMeter() { return nukeMeter; }

    void setInvisible(int invisible_in) { invisible = invisible_in; };
    int getInvisible() { return invisible; }
    
    void setMaxSpeedAttained(int maxSpeedAttained_in) { maxSpeedAttained = maxSpeedAttained_in; };
    bool getMaxSpeedAttained() { return maxSpeedAttained; }

    void setShowLevel(int showLevel_in) { showLevel = showLevel_in; };
    int getShowLevel() { return showLevel; }

    void setThrusting(bool thrusting_in) { thrusting = thrusting_in; };
    bool getThrusting() { return thrusting; }

    void setTurnState(TurnState w_state) { turnState = w_state; };
    TurnState getTurnState() { return turnState; };
    void renderRaster(QPainter &painter, QImage image);

public:
    // ==============================================================
    // FIELDS
    // ==============================================================

    //static fields

    //number of degrees the falcon will turn at each animation cycle if the turnState is LEFT or RIGHT
    const static int TURN_STEP = 11;
    //number of frames that the falcon will be protected after a spawn
    static const int INITIAL_SPAWN_TIME = 46;
    //number of frames falcon will be protected after consuming a NewShieldFloater
    static const int MAX_SHIELD = 200;
    static const int MAX_NUKE = 600;

    static const int MIN_RADIUS = 14;


private:
    //instance fields
    int shield;
    int nukeMeter;
    int invisible;
    bool maxSpeedAttained;
    int showLevel;
    bool thrusting;
    //enum used for turnState field
    TurnState turnState = IDLE;

    QMap<ImageState, QImage> rasterMap;

};

#endif // FALCON_H
