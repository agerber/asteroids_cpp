#include "NukeFloater.h"
#include "Game.h"

int NukeFloater::SPAWN_NUKE_FLOATER = Game::FRAMES_PER_SECOND * 50;

NukeFloater::NukeFloater() : Floater() {
    setColor(color);
    setExpiry(expiry);
}



/**
#include "NukeFloater.h"
#include "Game.h"
    
int NukeFloater::SPAWN_NUKE_FLOATER = Game::FRAMES_PER_SECOND * 50;

NukeFloater::NukeFloater() : Floater() {
    setColor(color);
    setExpiry(expiry);
}
**/
