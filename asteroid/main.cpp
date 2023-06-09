#include <QApplication>
#include <QThread>
#include "Game.h"
#include "QDebug"
#include <QStringList>

#define QDEBUGS QStringList

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // typical Qt application start
    // call QObject threading object to move object to another thread
  //  GamePanel *gamePanel= new GamePanel(nullptr, Game::DIM);
    // add key listener to the game panel
  //  gamePanel->setMinimumSize(Game::DIM.width(), Game::DIM.height());

    /*
    QThread::create([&app](){
        auto game = new Game();
        game->setGamePanel(gamePanel);
       // game->show();
   //     return app.exec();
    })->start();
     //
     */
     auto game = new Game();
     game->start();

     QDEBUGS() << "this is a test";

    return app.exec();
}