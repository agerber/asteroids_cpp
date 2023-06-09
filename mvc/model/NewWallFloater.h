#ifndef NEWWALLFLOATER_H
#define NEWWALLFLOATER_H

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

#endif // NEWWALLFLOATER_H