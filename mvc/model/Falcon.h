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
    static const int MIN_RADIUS = 28;

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
    Falcon() {
        setTeam(Team::FRIEND);
        setRadius(MIN_RADIUS);
        shield = 0;
        nukeMeter = 0;
        invisible = 0;
        maxSpeedAttained = false;
        showLevel = 0;
        thrusting = false;
        turnState = TurnState::IDLE;

        // Load images
        std::map<ImageState, std::shared_ptr<sf::Texture>> rasterMap;
        rasterMap[ImageState::FALCON_INVISIBLE] = nullptr;
        rasterMap[ImageState::FALCON] = loadGraphic("imgs/fal/falcon125.png");
        rasterMap[ImageState::FALCON_THR] = loadGraphic("imgs/fal/falcon125_thr.png");
        rasterMap[ImageState::FALCON_PRO] = loadGraphic("imgs/fal/falcon125_PRO.png");
        rasterMap[ImageState::FALCON_PRO_THR] = loadGraphic("imgs/fal/falcon125_PRO_thr.png");

        //setRasterMap( rasterMap );

    }

    // Check if the Falcon is protected
    bool isProtected() const override {
        return shield > 0;
    }

    // Move the Falcon
    void move() override {
        Sprite::move();

        if (invisible > 0) invisible--;
        if (shield > 0) shield--;
        if (nukeMeter > 0) nukeMeter--;
        if (showLevel > 0) showLevel--;

        const double THRUST = 0.85;
        const int MAX_VELOCITY = 39;

        if (thrusting) {
            double vectorX = std::cos(getOrientation() * M_PI / 180.0) * THRUST;
            double vectorY = std::sin(getOrientation() * M_PI / 180.0) * THRUST;

            int absVelocity = static_cast<int>(std::sqrt(
                std::pow(getDeltaX() + vectorX, 2) + std::pow(getDeltaY() + vectorY, 2)));

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
        case TurnState::LEFT:
            adjustOr = (getOrientation() <= 0) ? 360 - TURN_STEP : getOrientation() - TURN_STEP;
            break;
        case TurnState::RIGHT:
            adjustOr = (getOrientation() >= 360) ? TURN_STEP : getOrientation() + TURN_STEP;
            break;
        case TurnState::IDLE:
        default:
            break;
        }
        setOrientation(adjustOr);
    }

    // Draw the Falcon
    void draw(sf::RenderWindow& window) override {
        ImageState imageState;
        if (invisible > 0) {
            imageState = ImageState::FALCON_INVISIBLE;
        } else if (isProtected()) {
            imageState = thrusting ? ImageState::FALCON_PRO_THR : ImageState::FALCON_PRO;
            drawShield(window);
        } else {
            imageState = thrusting ? ImageState::FALCON_THR : ImageState::FALCON;
        }

        // Render based on image state
        renderRaster( window, getRasterMap()[static_cast<int>(imageState)] );
    }

private:
    int shield;
    int nukeMeter;
    int invisible;
    bool maxSpeedAttained;
    int showLevel;
    bool thrusting;
    TurnState turnState;

    // Draw the shield around the Falcon
    void drawShield(sf::RenderWindow& window) {
        sf::CircleShape shieldShape(getRadius());
        shieldShape.setOutlineColor(sf::Color::Cyan);
        shieldShape.setOutlineThickness(1);
        shieldShape.setFillColor(sf::Color::Transparent);
        shieldShape.setPosition(getCenter().x - getRadius(), getCenter().y - getRadius());
        window.draw(shieldShape);
    }
};

#endif
