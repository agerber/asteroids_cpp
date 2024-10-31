#ifndef FALCON_H
#define FALCON_H

#include "Sprite.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <cmath>

class Falcon : public Sprite {
public:
    // Constants
    static const int TURN_STEP = 11;
    static const int INITIAL_SPAWN_TIME = 46;
    static const int MAX_SHIELD = 200;
    static const int MAX_NUKE = 600;
    static const int MIN_RADIUS = 14;

    enum class ImageState {
        FALCON_INVISIBLE, // For pre-spawning
        FALCON,           // Normal ship
        FALCON_THR,       // Normal ship thrusting
        FALCON_PRO,       // Protected ship (green)
        FALCON_PRO_THR    // Protected ship (green) thrusting
    };

    enum class TurnState { IDLE, LEFT, RIGHT };


    void setThrusting(bool value) { thrusting = value; }
    void setTurnState(TurnState state) { turnState = state; }
    void setShield(int value) { shield = value; }
    void setShowLevel(int value) { showLevel = value; }
    void setNukeMeter(int value) { nukeMeter = value; }
    void setMaxSpeedAttained(bool value) { maxSpeedAttained = value; }
    void setInvisible(int value) { invisible = value; }

    int getShowLevel() const { return showLevel; }
    int getThrusting() const { return thrusting; }
    TurnState getTurnState() const { return turnState; }
    int getShield() const { return shield; }
    int getNukeMeter() const { return nukeMeter; }
    bool isMaxSpeedAttained() const { return maxSpeedAttained; }

    // Constructor
    Falcon();

    // Check if the Falcon is protected
    bool isProtected() const override { return shield > 0; }

    // Move the Falcon
    void move() override;

    // Draw the Falcon
    void draw(sf::RenderWindow& window) override;

private:
    int shield;
    int nukeMeter;
    int invisible;
    bool maxSpeedAttained;
    int showLevel;
    bool thrusting;
    TurnState turnState;

    // Draw the shield around the Falcon
    void drawShield(sf::RenderWindow& window);

};

#endif
