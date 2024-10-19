
#include "Star.h"
#include "Game.h"




Star::Star()
{
    // Randomize the position within the game dimensions
    center = sf::Vector2f(Game::R() % Game::DIM.x, Game::R() % Game::DIM.y);
    int bright = Game::R() % 226; // Stars are muted at max brightness of 225 out of 255
    color = sf::Color(bright, bright, bright); // some grey value
}
