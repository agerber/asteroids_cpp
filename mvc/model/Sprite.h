#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include "Movable.h"
#include "PolarPoint.h"
#include "Utils.h"
#include "GameOp.h"




class Sprite: public Movable {

public:
    Sprite();

    // Getters and setters
    void setCenter(const sf::Vector2f& c) { center = c; }
    virtual sf::Vector2f getCenter() const override { return center; }

    void setRadius(int r) { radius = r; }
    virtual int getRadius() const override { return radius; }

    void setTeam(Team t) { team = t; }
    virtual Team getTeam() const override { return team; }


    virtual bool isProtected() const override {
        return false; // By default, sprites are not protected
    }

    void setDeltaX(double dx) { deltaX = dx; }
    double getDeltaX() const { return deltaX; }

    void setDeltaY(double dy) { deltaY = dy; }
    double getDeltaY() const { return deltaY; }


    void setOrientation(int o) { orientation = o; }
    int getOrientation() const { return orientation; }

    void setExpiry(int e) { expiry = e; }
    int getExpiry() const { return expiry; }

    void setSpin(int s) { spin = s; }
    int getSpin() const { return spin; }

    void setCartesians(const std::vector<sf::Vector2f>& c) { cartesians = c; }
    std::vector<sf::Vector2f> getCartesians() const { return cartesians; }

    void setColor(const sf::Color& c) { color = c; }
    sf::Color getColor() const { return color; }

    void setRasterMap(const std::map<int, std::shared_ptr<sf::Texture>>& map) { rasterMap = map; }
    std::map<int, std::shared_ptr<sf::Texture>> getRasterMap() const { return rasterMap; }


protected:
    virtual void draw(sf::RenderWindow& window) override = 0;

    virtual void move() override;

    int somePosNegValue(int seed);

    void renderVector(sf::RenderWindow& window);
    std::shared_ptr<sf::Texture> loadGraphic(const std::string& imagePath);
    void renderRaster(sf::RenderWindow& window, const std::shared_ptr<sf::Texture>& texture);
    void renderRaster(sf::RenderWindow& window, const std::shared_ptr<sf::Texture>& texture, int diam);

private:
    sf::Vector2f center;
    double deltaX = 0, deltaY = 0;
    Team team;
    int radius = 0;
    int orientation = 0;
    int expiry = 0;
    int spin = 0;
    std::vector<sf::Vector2f> cartesians;
    sf::Color color;
    std::map<int, std::shared_ptr<sf::Texture>> rasterMap;

    void expire();
};



#endif
