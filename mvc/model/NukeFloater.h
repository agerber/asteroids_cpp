#ifndef NUKEFLOATER_H
#define NUKEFLOATER_H

#include "Floater.h"

class NukeFloater : public Floater {
public:
    static const int SPAWN_NUKE_FLOATER;

    NukeFloater() {
        setColor(sf::Color::Yellow);
        setExpiry(120);
    }
};



#endif // NUKEFLOATER_H
