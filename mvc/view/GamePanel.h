#ifndef GAMEPANEL_H
#define GAMEPANEL_H

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

#endif // GAMEPANEL_H
