#ifndef NEWWALLFLOATER_H
#define NEWWALLFLOATER_H



#include "Floater.h"
#include <SFML/Graphics.hpp>

class NewWallFloater : public Floater {
public:
    NewWallFloater();
    ~NewWallFloater() = default;

    static int SPAWN_NEW_WALL_FLOATER;

private:
    sf::Color MAROON = sf::Color(186, 0, 22);
};

/**
#include "Floater.h"
#include "Game.h"
#include <QColor>

class NewWallFloater : public Floater
{
public:
    //spawn every 40 seconds
    NewWallFloater();
    ~NewWallFloater() {}
    static  int SPAWN_NEW_WALL_FLOATER; 

private:
    QColor MAROON{ 186, 0, 22 };
};
**/


#endif // NEWWALLFLOATER_H
