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
