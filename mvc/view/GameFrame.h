#ifndef GAMEFRAME_H
#define GAMEFRAME_H


#include <SFML/Graphics.hpp>

class GameFrame : public sf::RenderWindow {
public:
    GameFrame();
    ~GameFrame();

private:
    void initialize();
    void handleCloseEvent();
};

/**
#include <QWidget>
#include <QLayout>

class GameFrame : public QWidget {
    Q_OBJECT

public:
    GameFrame(QWidget *parent = nullptr);

private:
    void initialize();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QVBoxLayout *layout;
};
**/


#endif // GAMEFRAME_H
