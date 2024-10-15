#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <atomic>
#include "GamePanel.h"
#include "CommandCenter.h"
#include "Brick.h"
#include "Asteroid.h"
#include "Floater.h"
#include "WhiteCloudDebris.h"
#include "ShieldFloater.h"
#include "NewWallFloater.h"
#include "NukeFloater.h"
#include "Bullet.h"
#include "Nuke.h"

class GamePanel;

class Game {
public:
    static const sf::Vector2u DIM;
    static const int ANIMATION_DELAY;
    static const int FRAMES_PER_SECOND;

    Game();
    ~Game();

    void run();
    void stop();

    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

    void keyPressEvent(const sf::Event &event);
    void keyReleaseEvent(const sf::Event &event);
private:
    void checkFloaters();
    void checkCollisions();
    void processGameOpsQueue();

    void buildWall();
    void spawnNewWallFloater();
    void spawnShieldFloater();
    void spawnNukeFloater();
    void spawnBigAsteroids(int num);
    void spawnSmallerAsteroidsOrDebris(Asteroid* originalAsteroid);

    bool isBrickFree();
    bool isLevelClear();
    void checkNewLevel();

    std::thread animationThread;
    std::atomic<bool> running;

    GamePanel* m_pGamePanel;
    sf::SoundBuffer soundThrustBuffer;
    sf::SoundBuffer soundBackgroundBuffer;
    sf::Sound soundThrust;
    sf::Sound soundBackground;
};
/**
#include <QMainWindow>
#include <QKeyEvent>
#include "GamePanel.h"
#include "Sound.h"
#include "CommandCenter.h"
#include "Falcon.h"
#include "Brick.h"
#include "Floater.h"
#include "Asteroid.h"

#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
class Game : public QThread
{
    Q_OBJECT

public:
    // ===============================================
    // FIELDS
    // ===============================================
    static const QSize DIM;
    static const int ANIMATION_DELAY;
    static const int FRAMES_PER_SECOND;

    GamePanel *m_pGamePanel;
    static const int PAUSE = Qt::Key_P; // p key
    static const int QUIT = Qt::Key_Q; // q key
    static const int LEFT = Qt::Key_Left; // rotate left; left arrow
    static const int RIGHT = Qt::Key_Right; // rotate right; right arrow
    static const int UP = Qt::Key_Up; // thrust; up arrow
    static const int START = Qt::Key_S; // s key
    static const int FIRE = Qt::Key_Space; // space key
    static const int MUTE = Qt::Key_M; // m-key mute
    static const int NUKE = Qt::Key_N; // n-key mute


    // ===============================================
    // ==CONSTRUCTOR
    // ===============================================
    Game(QObject *parent = nullptr);

    // ===============================================
    // ==METHODS
    // ===============================================
    void checkFloaters();
    void checkCollisions();
    void processGameOpsQueue();

    // Game implements runnable, and must have run method
    void run() override;

    void setGraphics();
    
    void  setGamePanel(GamePanel* gamePanel);
signals:
    // Expose signals that are not part of QMainWindow, but are needed.
    void quit();
    void start();
    void pause();
    void unmute();
    void mute();

private: 

    void buildWall();
    void spawnNewWallFloater();
    void spawnShieldFloater();
    void spawnNukeFloater();
    void spawnBigAsteroids(int num);
    void spawnSmallerAsteroidsOrDebris(Asteroid* originalAsteroid);

    bool isBrickFree();
    bool isLevelClear();
    void checkNewLevel();
    static void stopLoopingSounds(QSoundEffect* soundThrust, QSoundEffect* soundBackground);

public slots:
  //  void update();

  //  void tick();

public:
    // ===============================================
    // ==METHODS
    // ===============================================
    // Overridden methods from QMainWindow and KeyListener.
   // void keyPressEvent(QKeyEvent *event) override;
   // void keyReleaseEvent(QKeyEvent *event) override;
    void keyPressEvent(QKeyEvent *event) ;
    void keyReleaseEvent(QKeyEvent *event) ;


private:
    QThread *animationThread;
    QSoundEffect* soundThrust;
    QSoundEffect* soundBackground;
};
**/

#endif // GAME_H
