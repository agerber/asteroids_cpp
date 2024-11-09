#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include "Sprite.h"

// Replace with your actual classes
class CommandCenter;
class Asteroid;
class NukeFloater;
class Falcon;
class Nuke;

class AspectRatio {
public:
    double width;
    double height;

    AspectRatio(double w, double h) : width(w), height(h) {}

    AspectRatio scale(double factor) const {
        return AspectRatio(width * factor, height * factor);
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }
};




class MiniMap : public Sprite {
private:
    const double MINI_MAP_PERCENT = 0.31;

    AspectRatio aspectRatio{1.0, 1.0};

    const sf::Color PUMPKIN = sf::Color(200, 100, 50);
    const sf::Color LIGHT_GRAY = sf::Color(200, 200, 200);

public:
    MiniMap() {
        setTeam(Team::DEBRIS);
    }

    void move() override{}

    void draw(sf::RenderWindow& window) override;

private:
    sf::Vector2f translatePoint(const sf::Vector2f& point) const;

    AspectRatio aspectAdjustedRatio(const sf::Vector2u& universeDim) const;
};

#endif // MINIMAP_H
