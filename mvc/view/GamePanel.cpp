
#include "GamePanel.h"
#include "Game.h"
#include "assetsloader.h"
#include "Asteroid.h"

GamePanel::GamePanel(sf::RenderWindow &win, Game *game)
    : window(win), game_(game)
{
    initFontInfo();
    initShipPoints();
    initOffscreenBuffer();
}

void GamePanel::update()
{
    // Offscreen image for double buffering
    window.clear(sf::Color::Black);
    drawNumFrame();

    if (CommandCenter::getInstance()->isGameOver()) {
        displayTextOnScreen({
            "GAME OVER",
            "use the arrow keys to turn and thrust",
            "use the space bar to fire",
            "'S' to Start",
            "'P' to Pause",
            "'Q' to Quit",
            "'M' to toggle music"
        });
    } else if (CommandCenter::getInstance()->isPaused()) {
        displayTextOnScreen({"Game Paused"});
    } else {
        moveDrawMovables({
            CommandCenter::getInstance()->getMovDebris(),
            CommandCenter::getInstance()->getMovFloaters(),
            CommandCenter::getInstance()->getMovFoes(),
            CommandCenter::getInstance()->getMovFriends()
        });

        //drawNumberShipsRemaining();
        //drawMeters();
        //drawFalconStatus();
    }

    // Display the offscreen buffer
    window.display();
}

void GamePanel::initFontInfo()
{
    auto font = AssetsLoader::instance()->useFont(GAME_PANEL_FONT_NAME);
    if (font) {
        text.setFont( *font.get() );
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
    } else {
        std::cout << "Font not loaded " << GAME_PANEL_FONT_NAME << "!";
    }
}

void GamePanel::initShipPoints()
{
    pntShipsRemaining = {
        {0, 9}, {-1, 6}, {-1, 3}, {-4, 1}, {4, 1}, {-4, 1}, {-4, -2}, {-1, -2}, {-1, -9},
        {-1, -2}, {-4, -2}, {-10, -8}, {-5, -9}, {-7, -11}, {-4, -11}, {-2, -9}, {-2, -10},
        {-1, -10}, {-1, -9}, {1, -9}, {1, -10}, {2, -10}, {2, -9}, {4, -11}, {7, -11},
        {5, -9}, {10, -8}, {4, -2}, {1, -2}, {1, -9}, {1, -2}, {4, -2}, {4, 1}, {1, 3},
        {1, 6}, {0, 9}
    };
}

void GamePanel::initOffscreenBuffer()
{
    offscreenBuffer.create(Game::DIM.x, Game::DIM.y);
}

void GamePanel::drawNumFrame()
{
    text.setString("FRAME: " + std::to_string(CommandCenter::getInstance()->getFrame()));
    text.setPosition(10, Game::DIM.y - 30);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void GamePanel::drawFalconStatus()
{

    // Score
    text.setString("Score: " + std::to_string(CommandCenter::getInstance()->getScore()));
    text.setPosition(10, 10);
    window.draw(text);

    // Level
    std::string levelText = "Level: " + std::to_string(CommandCenter::getInstance()->getLevel());
    text.setString(levelText);
    text.setPosition(20, 30);
    window.draw(text);

    // Status
    std::vector<std::string> statusArray;
    if (CommandCenter::getInstance()->getFalcon()->getShowLevel() > 0)
        statusArray.push_back(levelText);
    if (CommandCenter::getInstance()->getFalcon()->isMaxSpeedAttained())
        statusArray.push_back("WARNING - SLOW DOWN");
    if (CommandCenter::getInstance()->getFalcon()->getNukeMeter() > 0)
        statusArray.push_back("PRESS N for NUKE");

    displayTextOnScreen(statusArray);
}

void GamePanel::drawMeters()
{
    int shieldValue = CommandCenter::getInstance()->getFalcon()->getShield() / 2;
    int nukeValue = CommandCenter::getInstance()->getFalcon()->getNukeMeter() / 6;

    drawOneMeter(sf::Color::Cyan, 1, shieldValue);
    drawOneMeter(sf::Color::Yellow, 2, nukeValue);
}

void GamePanel::drawOneMeter(sf::Color color, int offset, int percent)
{
    int xVal = Game::DIM.x - (100 + 120 * offset);
    int yVal = Game::DIM.y - 45;

    sf::RectangleShape meter(sf::Vector2f(percent, 10));
    meter.setPosition(xVal, yVal);
    meter.setFillColor(color);
    window.draw(meter);

    sf::RectangleShape grayBox(sf::Vector2f(100, 10));
    grayBox.setPosition(xVal, yVal);
    grayBox.setOutlineColor(sf::Color::Black);
    grayBox.setOutlineThickness(1);
    window.draw(grayBox);
}

void GamePanel::drawNumberShipsRemaining()
{
    int numFalcons = CommandCenter::getInstance()->getNumFalcons();
    while (numFalcons > 0) {
        drawOneShip(numFalcons--);
    }
}

void GamePanel::drawOneShip(int offset)
{
    sf::ConvexShape ship;
    ship.setPointCount(pntShipsRemaining.size());
    for (size_t i = 0; i < pntShipsRemaining.size(); ++i) {
        ship.setPoint(i, pntShipsRemaining[i]);
    }

    ship.setFillColor(sf::Color(255, 165, 0));
    ship.setPosition(Game::DIM.x - (27 * offset), Game::DIM.y - 45);
    window.draw(ship);
}

void GamePanel::displayTextOnScreen(const std::vector<std::string> &lines)
{
    int yOffset = 0;
    for (const auto& line : lines) {
        text.setString(line);
        text.setPosition((Game::DIM.x - text.getGlobalBounds().width) / 2, Game::DIM.y / 4 + yOffset);
        yOffset += 40;
        window.draw(text);
    }
}

void GamePanel::moveDrawMovables(const std::vector<std::list<std::shared_ptr<Movable> > > &teams)
{
    for (const auto& team : teams) {
        for (const auto& movable : team) {
            if (movable) {
                movable->move();
                movable->draw(window);
            }
        }
    }
}
