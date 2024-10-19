#include "ShieldFloater.h"


int ShieldFloater::SPAWN_SHIELD_FLOATER()
{
    const int ret = Game::FRAMES_PER_SECOND() * 25;
    return ret;
}
