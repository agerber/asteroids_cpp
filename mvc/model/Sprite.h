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

    void renderVector(sf::RenderWindow& window)
    {
        sf::ConvexShape polygon;
        polygon.setPointCount(cartesians.size());

        // Adjust cartesians for location and apply transformations
        for (size_t i = 0; i < cartesians.size(); ++i) {
            float x = cartesians[i].x * radius * std::sin(orientation * (3.14159 / 180)) + center.x;
            float y = cartesians[i].y * radius * std::cos(orientation * (3.14159 / 180)) + center.y;
            polygon.setPoint(i, sf::Vector2f(x, y));
        }

        polygon.setFillColor(color);
        window.draw(polygon);
    }
    std::shared_ptr<sf::Texture> loadGraphic(const std::string& imagePath)
    {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(imagePath)) {
            std::cerr << "Error loading image: " << imagePath << std::endl;
            return nullptr;
        }
        return texture;
    }
    void renderRaster(sf::RenderWindow& window, const std::shared_ptr<sf::Texture>& texture)
    {
        if (!texture) return;

        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setPosition(center.x - radius, center.y - radius);
        sprite.setRotation(orientation);
        sprite.setScale(static_cast<float>(radius) * 2 / texture->getSize().x,
                        static_cast<float>(radius) * 2 / texture->getSize().y);
        window.draw(sprite);
    }

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
