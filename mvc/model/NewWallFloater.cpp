#include "newwallFloater.h"

#include "Game.h"

NewWallFloater::NewWallFloater() {
    setColor(MAROON);
    setExpiry(230);
}

int NewWallFloater::SPAWN_NEW_WALL_FLOATER = Game::FRAMES_PER_SECOND * 40;



/**

NewWallFloater::NewWallFloater()
{
    setColor(MAROON);
    setExpiry(230);
}

int NewWallFloater::SPAWN_NEW_WALL_FLOATER = Game::FRAMES_PER_SECOND * 40;


**/
