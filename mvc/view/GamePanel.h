#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Utils.h"
#include "PolarPoint.h"
#include "Movable.h"
#include "assetsloader.h"
#include <list>

class Game;
class GamePanel {
public:
    GamePanel(sf::RenderWindow& win, Game* game);

    void update();

private:
    sf::RenderWindow& window;
    sf::Text text;
    std::vector<sf::Vector2f> pntShipsRemaining;
    sf::Image imgOff;
    sf::RenderTexture offscreenBuffer;
    Game* game_;

    void initFontInfo();

    void initShipPoints();

    void initOffscreenBuffer();

    void drawNumFrame();

    void drawFalconStatus();

    void drawMeters();
    void drawOneMeter(sf::Color color, int offset, int percent);

    void drawNumberShipsRemaining();
    void drawOneShip(int offset);

    void displayTextOnScreen(const std::vector<std::string>& lines);

    void moveDrawMovables(const std::vector<std::list<std::shared_ptr<Movable>>>& teams);
};

#endif // GAMEPANEL_H
