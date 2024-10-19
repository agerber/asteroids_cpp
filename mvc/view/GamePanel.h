#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Utils.h"
#include "PolarPoint.h"
#include "Movable.h"
#include <list>

class GamePanel {
public:
    GamePanel(sf::RenderWindow& win) : window(win) {
        initFontInfo();
        initShipPoints();
        initOffscreenBuffer();
    }

    void update();

private:
    sf::RenderWindow& window;
    sf::Font fontNormal;
    sf::Font fontBig;
    sf::Text text;
    std::vector<sf::Vector2f> pntShipsRemaining;
    sf::Image imgOff;
    sf::RenderTexture offscreenBuffer;

    void initFontInfo() {
        if (!fontNormal.loadFromFile("SansSerif-Bold.ttf")) {
            // Handle error
        }
        if (!fontBig.loadFromFile("SansSerif-BoldItalic.ttf")) {
            // Handle error
        }
        text.setFont(fontNormal);
        text.setCharacterSize(12);
    }

    void initShipPoints() {
        pntShipsRemaining = {
            {0, 9}, {-1, 6}, {-1, 3}, {-4, 1}, {4, 1}, {-4, 1}, {-4, -2}, {-1, -2}, {-1, -9},
            {-1, -2}, {-4, -2}, {-10, -8}, {-5, -9}, {-7, -11}, {-4, -11}, {-2, -9}, {-2, -10},
            {-1, -10}, {-1, -9}, {1, -9}, {1, -10}, {2, -10}, {2, -9}, {4, -11}, {7, -11},
            {5, -9}, {10, -8}, {4, -2}, {1, -2}, {1, -9}, {1, -2}, {4, -2}, {4, 1}, {1, 3},
            {1, 6}, {0, 9}
        };
    }

    void initOffscreenBuffer();

    void drawNumFrame();

    void drawFalconStatus();

    void drawMeters();
    void drawOneMeter(sf::Color color, int offset, int percent);

    void drawNumberShipsRemaining();
    void drawOneShip(int offset);

    void displayTextOnScreen(const std::vector<std::string>& lines);

    void moveDrawMovables(const std::vector<std::list<std::shared_ptr<Movable>>>& teams) {
        for (const auto& team : teams) {
            for (const auto& movable : team) {
                if (movable) {
                    movable->move();
                    movable->draw(window);
                }
            }
        }
    }
};

#endif // GAMEPANEL_H
