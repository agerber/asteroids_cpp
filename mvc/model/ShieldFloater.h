#ifndef SHIELDFLOATER_H
#define SHIELDFLOATER_H

#include "Floater.h"
#include "Game.h"
#include <QColor>

class ShieldFloater : public Floater {
public:
    // spawn every 25 seconds
    static  int SPAWN_SHIELD_FLOATER;
    ShieldFloater() {
        setColor(QColor(Qt::cyan));
        setExpiry(260);
    }
};
int ShieldFloater::SPAWN_SHIELD_FLOATER = Game::FRAMES_PER_SECOND * 25;

#endif // SHIELDFLOATER_H