#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Movable.h"
#include "Game.h"

class Game;


class GamePanel {
public:
    GamePanel(const sf::Vector2u& size);
    ~GamePanel();

    void setGameParent(Game* pGame);

    void handleInput(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

private:
    void drawFalconStatus(sf::RenderWindow& window);
    void drawNumFrame(sf::RenderWindow& window);
    void drawMeters(sf::RenderWindow& window);
    void drawOneMeter(sf::RenderWindow& window, sf::Color color, int offSet, int percent);
    void moveDrawMovables(sf::RenderWindow& window, std::vector<Movable*>& teams);
    void drawNumberShipsRemaining(sf::RenderWindow& window);
    void drawOneShip(sf::RenderWindow& window, int offSet);
    void displayTextOnScreen(sf::RenderWindow& window, const std::vector<std::string>& text);

    sf::Font fontNormal;
    sf::Font fontBig;
    sf::Text text;

    std::vector<sf::Vector2f> pntShipsRemaining;
    Game* m_parentGame;
};

/**
#include <QWidget>
#include <QFont>
#include <QFontMetrics>
#include <QPoint>
#include <QFontMetrics>

#include "Movable.h"

class Game;

class GamePanel : public QWidget
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr, const QSize &size = QSize());
    ~GamePanel();

    void    setGameParent(Game* pGame);

protected:
    void paintEvent(QPaintEvent *event) override;

    void drawFalconStatus(QPainter &painter);
    void drawNumFrame(QPainter* painter);
    void drawMeters(QPainter* painter);

    void drawOneMeter(QPainter* painter, QColor color, int offSet, int percent);
    void moveDrawMovables(QPainter* painter, QVector<Movable*> &teams);

//    QVector<QPointF> cartesianToPolar(QVector<QPointF>  polygon);
//    QVector<QPointF> rotatePolarBy90(QVector<QPointF> points);
//
//    QVector<QPointF> polarToCartesian(QVector<QPointF> polarPoints);

    void drawNumberShipsRemaining(QPainter* painter);
    void drawOneShip(QPainter* painter, int offSet);

    void displayTextOnScreen(QPainter* painter, QStringList text);

protected:
    // ===============================================
    // ==METHODS
    // ===============================================
    // Overridden methods from QMainWindow and KeyListener.
   // void keyPressEvent(QKeyEvent *event) override;
   // void keyReleaseEvent(QKeyEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QFont fontNormal;
    QFont fontBig;
    QFontMetrics* fontMetrics;
    int fontWidth;
    int fontHeight;
    QVector<QPoint> pntShipsRemaining;

    Game* m_parentGame;
};
**/

#endif // GAMEPANEL_H
