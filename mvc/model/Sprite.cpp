#include "Sprite.h"
#include "Game.h"

Sprite::Sprite()
{
    center = sf::Vector2f(Game::nextInt(Game::DIM.x),
                          Game::nextInt(Game::DIM.y));
}

void Sprite::move()
{
    // Right-bounds reached
    if (center.x > Game::DIM.x) {
        center.x = 1;
    } else if (center.x < 0) { // Left-bounds reached
        center.x = Game::DIM.x - 1;
    } else if (center.y > Game::DIM.y) { // Bottom-bounds reached
        center.y = 1;
    } else if (center.y < 0) { // Top-bounds reached
        center.y = Game::DIM.y - 1;
    } else {
        center.x += deltaX;
        center.y += deltaY;
    }

    // Expire on short-lived objects only
    if (expiry > 0) expire();

    // Adjust orientation for spinning objects
    if (spin != 0) orientation += spin;
}

int Sprite::somePosNegValue(int seed)
{
    int randomNumber = Game::nextInt(seed);
    return (randomNumber % 2 == 0) ? randomNumber : -randomNumber;
}

void Sprite::expire()
{
    if (expiry == 1) {
        CommandCenter::getInstance()->getOpsQueue().enqueue(shared_from_this(), GameOp::Action::REMOVE);
    }
    expiry--;
}
