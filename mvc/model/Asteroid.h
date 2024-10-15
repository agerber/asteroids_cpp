#ifndef ASTEROID_H
#define ASTEROID_H

#pragma once

#include "Sprite.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <algorithm>

class Game;  // forward declaration

class Asteroid : public Sprite {  // inherits from the correct base class

public:
    Asteroid(int size);  // constructor
    Asteroid(Asteroid& astExploded);  // overloaded constructor
    int getSize();  // conversion method
    std::vector<sf::Vector2f> generateVertices();  // generates random vertices
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // drawing function

public:
    const int LARGE_RADIUS = 110;
};

/**
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include "Sprite.h"  //or whatever base class Asteroid extends from.
#include <QVector>
#include <QPoint>

class Game;  //forward declaration

class Asteroid : public Sprite {  //make sure to inherit from the correct base class.

public:
    //constructor
    Asteroid(int size);

    //overloaded constructor
    Asteroid(Asteroid & astExploded);

    //conversion method
    int getSize();

    //converts PolarPoints to Cartesian Points and generates random vertices.
     QVector<QPoint> generateVertices();

    //drawing function
    void   draw(QPainter &painter) override;

public:
    const int LARGE_RADIUS = 110; //note: use of const variable that has a value known at compilation.

};
**/

#endif //ASTEROID_H
