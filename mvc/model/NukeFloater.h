#ifndef NUKEFLOATER_H
#define NUKEFLOATER_H

#include "Floater.h"
#include <SFML/Graphics.hpp>

class NukeFloater : public Floater {
public:
    NukeFloater();
    static int SPAWN_NUKE_FLOATER;

private:
    sf::Color color = sf::Color(255, 255, 0);
    int expiry = 120;
};


/**
#include "Floater.h"
#include <QColor>

class NukeFloater : public Floater {
public:
    NukeFloater();
    static int SPAWN_NUKE_FLOATER;
private:
    QColor color = QColor(255, 255, 0);
    int expiry = 120;
};
**/

#endif //NUKEFLOATER_H
