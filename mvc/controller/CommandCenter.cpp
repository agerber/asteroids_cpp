#include "CommandCenter.h"
#include "Game.h"

CommandCenter* CommandCenter::instance = nullptr;

void CommandCenter::generateStarField()
{
    int count = 100;
    while (count-- > 0) {
        opsQueue.enqueue(std::make_shared<Star>(), GameOp::Action::ADD);
    }
}

void CommandCenter::initFalconAndDecrementFalconNum()
{
    numFalcons--;
    if (isGameOver()) return;
    soundQueue.push("shipspawn.wav");
    soundCondVar.notify_one();
    falcon->setShield(Falcon::INITIAL_SPAWN_TIME);
    falcon->setInvisible(Falcon::INITIAL_SPAWN_TIME / 4);
    falcon->setCenter(sf::Vector2f(Game::DIM.x / 2, Game::DIM.y / 2));
    falcon->setOrientation(Game::nextInt(360 / Falcon::TURN_STEP) * Falcon::TURN_STEP);
    falcon->setDeltaX(0);
    falcon->setDeltaY(0);
    falcon->setRadius(Falcon::MIN_RADIUS);
    falcon->setMaxSpeedAttained(false);
    falcon->setNukeMeter(0);
}

Falcon *CommandCenter::getFalcon() const
{
    static Falcon falcon;
    return &falcon;
}
