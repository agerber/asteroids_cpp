#include "GamePanel.h"
#include "CommandCenter.h"
#include "Utils.h"
#include <iostream>

GamePanel::GamePanel(const sf::Vector2u& size) {
    // Initialize ship points
    pntShipsRemaining = {
        {0, 9}, {-1, 6}, {-1, 3}, {-4, 1}, {4, 1}, {-4, 1},
        {-4, -2}, {-1, -2}, {-1, -9}, {-1, -2}, {-4, -2},
        {-10, -8}, {-5, -9}, {-7, -11}, {-4, -11}, {-2, -9},
        {-2, -10}, {-1, -10}, {-1, -9}, {1, -9}, {1, -10},
        {2, -10}, {2, -9}, {4, -11}, {7, -11}, {5, -9},
        {10, -8}, {4, -2}, {1, -2}, {1, -9}, {1, -2},
        {4, -2}, {4, 1}, {1, 3}, {1, 6}, {0, 9}
    };

    // Load fonts
    if (!fontNormal.loadFromFile("resources/fonts/SansSerif.ttf") ||
        !fontBig.loadFromFile("resources/fonts/SansSerif.ttf")) {
        std::cerr << "Error loading fonts" << std::endl;
    }

    text.setFont(fontNormal);
    text.setCharacterSize(12);
}

GamePanel::~GamePanel() {
    pntShipsRemaining.clear();
}

void GamePanel::setGameParent(Game* pGame) {
    m_parentGame = pGame;
}

void GamePanel::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        m_parentGame->keyPressEvent(event);
    } else if (event.type == sf::Event::KeyReleased) {
        m_parentGame->keyReleaseEvent(event);
    }
}

void GamePanel::update() {
    // Update logic can go here
}

void GamePanel::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    drawNumFrame(window);

    if (CommandCenter::getInstance()->isGameOver()) {
        displayTextOnScreen(window, {
                                        "GAME OVER",
                                        "Use the arrow keys to turn and thrust",
                                        "Press space to fire",
                                        "'S' to Start", "'P' to Pause",
                                        "'Q' to Quit", "'M' to toggle music"
                                    });
    } else if (CommandCenter::getInstance()->getPaused()) {
        displayTextOnScreen(window, { "Game Paused" });
    } else {
        moveDrawMovables(window, CommandCenter::getInstance()->getMovDebris());
        moveDrawMovables(window, CommandCenter::getInstance()->getMovFloaters());
        moveDrawMovables(window, CommandCenter::getInstance()->getMovFoes());
        moveDrawMovables(window, CommandCenter::getInstance()->getMovFriends());

        drawNumberShipsRemaining(window);
        drawMeters(window);
        drawFalconStatus(window);
    }

    window.display();
}

void GamePanel::drawNumFrame(sf::RenderWindow& window) {
    text.setString("CPP : " + std::to_string(CommandCenter::getInstance()->getFrame()));
    text.setPosition(10, window.getSize().y - 30);
    window.draw(text);
}

void GamePanel::drawMeters(sf::RenderWindow& window) {
    int shieldValue = CommandCenter::getInstance()->getFalcon()->getShield() / 2;
    int nukeValue = CommandCenter::getInstance()->getFalcon()->getNukeMeter() / 6;
    drawOneMeter(window, sf::Color::Cyan, 1, shieldValue);
    drawOneMeter(window, sf::Color::Yellow, 2, nukeValue);
}

void GamePanel::drawOneMeter(sf::RenderWindow& window, sf::Color color, int offSet, int percent) {
    sf::RectangleShape meter(sf::Vector2f(percent, 10));
    meter.setFillColor(color);
    meter.setPosition(window.getSize().x - (100 + 120 * offSet), window.getSize().y - 45);
    window.draw(meter);
}

void GamePanel::moveDrawMovables(sf::RenderWindow& window, std::vector<Movable*>& teams) {
    for (auto* team : teams) {
        team->move();
        team->draw(window, sf::RenderStates::Default);
    }
}

void GamePanel::drawNumberShipsRemaining(sf::RenderWindow& window) {
    int numFalcons = CommandCenter::getInstance()->getNumFalcons();
    while (numFalcons > 0) {
        drawOneShip(window, numFalcons--);
    }
}

void GamePanel::drawOneShip(sf::RenderWindow& window, int offSet) {
    sf::CircleShape shipShape(10);
    shipShape.setFillColor(sf::Color(255, 165, 0));  // Orange color
    shipShape.setPosition(window.getSize().x - (27 * offSet), window.getSize().y - 45);
    window.draw(shipShape);
}

void GamePanel::displayTextOnScreen(sf::RenderWindow& window, const std::vector<std::string>& text) {
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/SansSerif.ttf")) {
        // Handle font loading error
        return;
    }

    sf::Text sfText;
    sfText.setFont(font);
    sfText.setCharacterSize(24);  // Example size, adjust as needed
    sfText.setFillColor(sf::Color::White);

    int spacer = 0;

    for (const auto& line : text) {
        sfText.setString(line);

        // Calculate centered position
        float x = (window.getSize().x - sfText.getGlobalBounds().width) / 2;
        float y = window.getSize().y / 4 + spacer;

        sfText.setPosition(x, y);
        window.draw(sfText);

        spacer += 40;
    }
}

void GamePanel::drawFalconStatus(sf::RenderWindow& window) {
    text.setString("Score: " + std::to_string(CommandCenter::getInstance()->getScore()));
    text.setPosition(10, 10);
    window.draw(text);

    text.setString("Level: " + std::to_string(CommandCenter::getInstance()->getLevel()));
    text.setPosition(20, 30);
    window.draw(text);
}




/**
#include "GamePanel.h"
#include <QPainter>
#include <QApplication>
//#include <QDesktopWidget>
#include "Stream.h"
#include "Sprite.h"
#include "CommandCenter.h"
#include "Game.h"
#include "Utils.h"
#include "Stream.h"

#include <QPainter>
#include <QTransform>
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>
#include <QtMath>

#include "Game.h"
#include "Utils.h"
#include <qtimer.h>

using namespace stream;
using namespace stream::op;

GamePanel::GamePanel(QWidget *parent, const QSize &size) : QWidget(parent)
{
    setFixedSize(size);

    // Robert Alef's awesome falcon design
    pntShipsRemaining << QPoint(0,9)
             << QPoint(-1, 6)
             << QPoint(-1,3)
             << QPoint(-4, 1)
             << QPoint(4,1)
             << QPoint(-4,1)
             << QPoint(-4, -2)
             << QPoint(-1, -2)
             << QPoint(-1, -9)
             << QPoint(-1, -2)
             << QPoint(-4, -2)
             << QPoint(-10, -8)
             << QPoint(-5, -9)
             << QPoint(-7, -11)
             << QPoint(-4, -11)
             << QPoint(-2, -9)
             << QPoint(-2, -10)
             << QPoint(-1, -10)
             << QPoint(-1, -9)
             << QPoint(1, -9)
             << QPoint(1, -10)
             << QPoint(2, -10)
             << QPoint(2, -9)
             << QPoint(4, -11)
             << QPoint(7, -11)
             << QPoint(5, -9)
             << QPoint(10, -8)
             << QPoint(4, -2)
             << QPoint(1, -2)
             << QPoint(1, -9)
             << QPoint(1, -2)
             << QPoint(4,-2)
             << QPoint(4, 1)
             << QPoint(1, 3)
             << QPoint(1,6)
             << QPoint(0,9);

    fontNormal = QFont("SansSerif", 12, QFont::Bold);
    fontBig = QFont("SansSerif", 36, QFont::Bold); //| QFont::Italic
    fontMetrics = new QFontMetrics(fontNormal);
    fontWidth = fontMetrics->averageCharWidth();
    fontHeight = fontMetrics->height();
}

GamePanel::~GamePanel()
{
    pntShipsRemaining.clear();
}

void GamePanel::setGameParent(Game* pGame)
{
    m_parentGame = pGame;
}



void GamePanel::drawNumFrame(QPainter* painter)
{
    painter->setFont(fontNormal);
    painter->setPen(Qt::white);
    painter->drawText(fontWidth, Game::DIM.height() - (fontHeight + 22), "CPP :  " + QString::number(CommandCenter::getInstance()->getFrame()));
}

void GamePanel::drawMeters(QPainter* painter)
{
    int shieldValue = CommandCenter::getInstance()->getFalcon()->getShield() / 2;
    int nukeValue = CommandCenter::getInstance()->getFalcon()->getNukeMeter() /6;
    drawOneMeter(painter, Qt::cyan, 1, shieldValue);
    drawOneMeter(painter, Qt::yellow, 2, nukeValue);
}

void GamePanel::drawOneMeter(QPainter* painter, QColor color, int offSet, int percent)
{
    int xVal = Game::DIM.width() - (100 + 120 * offSet);
    int yVal = Game::DIM.height() - 45;

    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawRect(xVal, yVal, percent, 10);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QColor(50, 50, 50));
    painter->drawRect(xVal, yVal, 100, 10);
}

void GamePanel::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    painter.fillRect(rect(), QColor(0, 0, 0));

    drawNumFrame(&painter);

    if (CommandCenter::getInstance()->isGameOver())
    {
        displayTextOnScreen(&painter,{
            "GAME OVER",
            "use the arrow keys to turn and thrust",
            "use the space bar to fire",
            "'S' to Start",
            "'P' to Pause",
            "'Q' to Quit",
            "'M' to toggle music"
        });
    }
    else if (CommandCenter::getInstance()->getPaused())
    {
        displayTextOnScreen(&painter,{"Game Paused"});
    }
    else
    {
        moveDrawMovables(&painter, CommandCenter::getInstance()->getMovDebris());
        moveDrawMovables(&painter, CommandCenter::getInstance()->getMovFloaters());
        moveDrawMovables(&painter ,CommandCenter::getInstance()->getMovFoes());
        moveDrawMovables(&painter ,CommandCenter::getInstance()->getMovFriends());

        drawNumberShipsRemaining(&painter);
        drawMeters(&painter);
        drawFalconStatus(painter);
    }
}

void GamePanel::moveDrawMovables(QPainter* painter, QVector<Movable*> &teams)
{
    auto moveDraw = [&](Movable* team) -> Movable*
    {
        team->move();
        team->draw(*painter);

        return team;
    };

    MakeStream::from(teams)
    | flat_map([](Movable* team) {
        return MakeStream::singleton(team);
    }) | map_(moveDraw) | to_vector();
}


void GamePanel::drawNumberShipsRemaining(QPainter* painter)
{
    int numFalcons = CommandCenter::getInstance()->getNumFalcons();
    while (numFalcons > 0)
    {
        drawOneShip(painter, numFalcons--);
    }
}

void GamePanel::drawOneShip(QPainter* painter, int offSet)
{

    QPen pen;
    pen.setColor(QColor(255, 165, 0));
    painter->setPen(pen);


    double degrees180 = 180.0;
    int radius = 20;
    int xVal = Game::DIM.width() - (27 * offSet);
    int yVal = Game::DIM.height() - 45;

    QVector<PolarPoint> polars = Utils::cartesianToPolar(pntShipsRemaining);

    auto rotatePolarBy90 = [&](const PolarPoint& pp) -> PolarPoint
    {
        return {pp.r, pp.theta + Utils::my_qDegreesToRadians(degrees180)}; //rotated Theta
    };

    auto polarToCartesian = [&](const PolarPoint& pp) -> QPointF
    {
        return QPointF(pp.r * radius * cos(pp.theta), pp.r * radius * sin(pp.theta));
    };

    auto adjustForLocation = [&](const QPointF& p) -> QPointF
    {
        return QPointF( p.x() + xVal, p.y() + yVal);
    };

    std::vector<QPointF> points = MakeStream::from(polars)
                                  | map_(rotatePolarBy90)
                                  | map_(polarToCartesian)
                                  | map_(adjustForLocation)
                                  | to_vector();

    painter->drawPolygon(points.data(), points.size());


}

void GamePanel::displayTextOnScreen(QPainter* painter, QStringList text)
{
    QFontMetrics metrics(fontNormal);
    int spacer = 0;
    //foreach (const QString& line, text) 
    for (int i = 0; i < text.length(); i++)
    {
        const QString& line = text.at(i);
        QRect bounds = metrics.boundingRect(line); // get the existing dimensions of the string
        int x = (Game::DIM.width() - bounds.width()) / 2;
        int y = Game::DIM.height() / 4 + fontHeight + spacer;
        painter->setPen(Qt::white);
        painter->setFont(fontNormal);
        painter->drawText(x, y, line);
        spacer += 40;
    }
}

void GamePanel::keyPressEvent(QKeyEvent* event)
{
    m_parentGame->keyPressEvent(event);
}

void GamePanel::keyReleaseEvent(QKeyEvent* event)
{
    m_parentGame->keyReleaseEvent(event);
}

void GamePanel::drawFalconStatus(QPainter &painter)
{
    QPen whitePen(Qt::white);
    QFont normalFont("Helvetica", 12, QFont::Normal);

    // Draw score always
    painter.setPen(whitePen);
    painter.setFont(normalFont);
    QString scoreText = "Score :  " + QString::number(CommandCenter::getInstance()->getScore());
    painter.drawText(fontWidth, fontHeight, scoreText);

    // Draw the level upper-left corner always
    QString levelText = "Level: " + QString::number(CommandCenter::getInstance()->getLevel());
    painter.drawText(20, 30, levelText); //upper-left corner

    // Build the status string array with possible messages in middle of screen
    QStringList statusArray;
    if (CommandCenter::getInstance()->getFalcon()->getShowLevel() > 0) {
        statusArray.append(levelText);
    }
    if (CommandCenter::getInstance()->getFalcon()->getMaxSpeedAttained()) {
        statusArray.append("WARNING - SLOW DOWN");
    }
    if (CommandCenter::getInstance()->getFalcon()->getNukeMeter() > 0) {
        statusArray.append("PRESS N for NUKE");
    }

    // Draw the statusArray strings to middle of screen
    if (statusArray.size() > 0)
        displayTextOnScreen(&painter, statusArray);
}
**/
