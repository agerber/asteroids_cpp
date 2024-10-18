#include "Game.h"

GamePanel *Game::gamePanel()
{
    static GamePanel gp;
    return &gp;
}
