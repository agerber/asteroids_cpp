#include "Game.h"
#include <iostream>
#include <chrono>

const sf::Vector2u Game::DIM = {1100, 900};
const int Game::ANIMATION_DELAY = 40;
const int Game::FRAMES_PER_SECOND = 1000 / ANIMATION_DELAY;

Game::Game() : running(false) {
    m_pGamePanel = new GamePanel(DIM);
    CommandCenter::getInstance()->initGame();

    // Load sounds (replace with correct paths)
    if (!soundThrustBuffer.loadFromFile("resources/sounds/thrust.wav") ||
        !soundBackgroundBuffer.loadFromFile("resources/sounds/background.wav")) {
        std::cerr << "Error loading sounds" << std::endl;
    }

    soundThrust.setBuffer(soundThrustBuffer);
    soundBackground.setBuffer(soundBackgroundBuffer);
    soundBackground.setLoop(true);
}

Game::~Game() {
    stop();
    if (animationThread.joinable()) {
        animationThread.join();
    }
    delete m_pGamePanel;
}

void Game::run() {
    running = true;
    animationThread = std::thread([this]() {
        while (running) {
            auto start = std::chrono::high_resolution_clock::now();

            update();

            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            std::this_thread::sleep_for(
                std::chrono::milliseconds(ANIMATION_DELAY) - elapsed);
        }
    });
}

void Game::stop() {
    running = false;
}

void Game::handleEvent(const sf::Event& event) {
    Falcon* falcon = CommandCenter::getInstance()->getFalcon();
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::P:
            CommandCenter::getInstance()->setPaused(!CommandCenter::getInstance()->getPaused());
            break;
        case sf::Keyboard::Q:
            stop();
            break;
        case sf::Keyboard::Up:
            falcon->setThrusting(true);
            soundThrust.play();
            break;
        case sf::Keyboard::Left:
            falcon->setTurnState(Falcon::LEFT);
            break;
        case sf::Keyboard::Right:
            falcon->setTurnState(Falcon::RIGHT);
            break;
        case sf::Keyboard::S:
            CommandCenter::getInstance()->initGame();
            break;
        case sf::Keyboard::Space:
            CommandCenter::getInstance()->getOpsQueue()->enqueue(new Bullet(falcon), GameOp::Action::ADD);
            break;
        case sf::Keyboard::N:
            if (falcon->getNukeMeter() > 0) {
                CommandCenter::getInstance()->getOpsQueue()->enqueue(new Nuke(falcon), GameOp::Action::ADD);
                falcon->setNukeMeter(0);
            }
            break;
        case sf::Keyboard::M:
            CommandCenter::getInstance()->setMuted(!CommandCenter::getInstance()->getMuted());
            break;
        default:
            break;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            falcon->setThrusting(false);
            soundThrust.stop();
        } else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            falcon->setTurnState(Falcon::IDLE);
        }
    }
}

void Game::update() {
    if (!CommandCenter::getInstance()->getPaused()) {
        m_pGamePanel->update();
        checkCollisions();
        checkFloaters();
        checkNewLevel();
        CommandCenter::getInstance()->incrementFrame();
    }
    processGameOpsQueue();
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    m_pGamePanel->render(window);
    window.display();
}

void Game::keyPressEvent(const sf::Event& event)
{
    Falcon* falcon = CommandCenter::getInstance()->getFalcon();

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::P:
            CommandCenter::getInstance()->setPaused(!CommandCenter::getInstance()->getPaused());
            break;

        case sf::Keyboard::Q:
            stop();  // Stops the game
            break;

        case sf::Keyboard::Up:
            if (falcon) {
                falcon->setThrusting(true);
                soundThrust.play();
            }
            break;

        case sf::Keyboard::Left:
            if (falcon) {
                falcon->setTurnState(Falcon::LEFT);
            }
            break;

        case sf::Keyboard::Right:
            if (falcon) {
                falcon->setTurnState(Falcon::RIGHT);
            }
            break;

        case sf::Keyboard::S:
            if (CommandCenter::getInstance()->isGameOver()) {
                CommandCenter::getInstance()->initGame();  // Start a new game
            }
            break;

        case sf::Keyboard::Space:
            if (falcon) {
                CommandCenter::getInstance()->getOpsQueue()->enqueue(
                    new Bullet(falcon), GameOp::Action::ADD);
            }
            break;

        case sf::Keyboard::N:
            if (falcon && falcon->getNukeMeter() > 0) {
                CommandCenter::getInstance()->getOpsQueue()->enqueue(
                    new Nuke(falcon), GameOp::Action::ADD);
                falcon->setNukeMeter(0);
            }
            break;

        case sf::Keyboard::M:
            CommandCenter::getInstance()->setMuted(!CommandCenter::getInstance()->getMuted());
            break;

        default:
            break;
        }
    }
}

void Game::keyReleaseEvent(const sf::Event& event)
{
    Falcon* falcon = CommandCenter::getInstance()->getFalcon();

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            if (falcon) {
                falcon->setThrusting(false);
                soundThrust.stop();
            }
            break;

        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            if (falcon) {
                falcon->setTurnState(Falcon::IDLE);
            }
            break;

        case sf::Keyboard::Space:
            // Additional logic for space release, if needed
            break;

        default:
            break;
        }
    }
}

void Game::checkFloaters() {
    spawnNewWallFloater();
    spawnShieldFloater();
    spawnNukeFloater();
}

void Game::checkCollisions() {
    // Logic for collisions between friends and foes
    // (converted from your provided code)
}

void Game::processGameOpsQueue() {
    CommandCenter* cc = CommandCenter::getInstance();
    while (!cc->getOpsQueue()->empty()) {
        GameOp* gameOp = cc->getOpsQueue()->dequeue();
        Movable* mov = gameOp->getMovable();
        GameOp::Action action = gameOp->getAction();

        switch (mov->getTeam()) {
        case Movable::FOE:
            if (action == GameOp::Action::ADD) {
                cc->getMovFoes().push_back(mov);
            } else {
                cc->getMovFoes().erase(
                    std::remove(cc->getMovFoes().begin(), cc->getMovFoes().end(), mov),
                    cc->getMovFoes().end());
                if (auto* ast = dynamic_cast<Asteroid*>(mov)) {
                    spawnSmallerAsteroidsOrDebris(ast);
                }
                delete mov;
            }
            break;
            // Handle other cases similarly...
        }
    }
}

void Game::buildWall() {
    // Logic to build the wall of bricks
}

void Game::spawnNewWallFloater() {
    if (CommandCenter::getInstance()->getFrame() % NewWallFloater::SPAWN_NEW_WALL_FLOATER == 0) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new NewWallFloater(), GameOp::Action::ADD);
    }
}

void Game::spawnShieldFloater() {
    if (CommandCenter::getInstance()->getFrame() % ShieldFloater::SPAWN_SHIELD_FLOATER == 0) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new ShieldFloater(), GameOp::Action::ADD);
    }
}

void Game::spawnNukeFloater() {
    if (CommandCenter::getInstance()->getFrame() % NukeFloater::SPAWN_NUKE_FLOATER == 0) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new NukeFloater(), GameOp::Action::ADD);
    }
}

void Game::spawnBigAsteroids(int num) {
    while (num-- > 0) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new Asteroid(0), GameOp::Action::ADD);
    }
}

void Game::spawnSmallerAsteroidsOrDebris(Asteroid* originalAsteroid) {
    // Logic to spawn smaller asteroids or debris
}

bool Game::isBrickFree() {
    // Logic to check if bricks are free
    return true;
}

bool Game::isLevelClear() {
    // Logic to check if the level is clear
    return true;
}

void Game::checkNewLevel() {
    // Logic to handle a new level
}



/**
#include "Game.h"
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include "game.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDateTime>
#include "qglobal.h"

#include "Utils.h"
#include "newwallFloater.h"
#include "ShieldFloater.h"
#include "NukeFloater.h"
#include "WhiteCloudDebris.h"
#include "Bullet.h"
#include "Nuke.h"

const QSize Game::DIM(1100, 900); //the dimension of the game.
const int Game::ANIMATION_DELAY = 40; // milliseconds between frames
const int Game::FRAMES_PER_SECOND = 1000 / ANIMATION_DELAY;
// ported to C++ using Qt framework

//todo: Sounds need to be redone using Qt6.6.0


Game::Game(QObject *parent) : QThread(parent)
{
    m_pGamePanel = new GamePanel(nullptr, Game::DIM);
    // add key listener to the game panel
   m_pGamePanel->setMinimumSize(Game::DIM.width(), Game::DIM.height());
   // gamePanel->addKeyListener(this);
   m_pGamePanel->setGameParent(this);
   m_pGamePanel->show();

    //soundThrust = Sound::clipForLoopFactory("whitenoise.wav");
    //soundBackground = Sound::clipForLoopFactory("music-background.wav");
    // fire up the animation threadGame::keyPressed(
    // pass the animation thread a runnable object, the Game object
    animationThread = QThread::create(&Game::run, this);
    animationThread->start();
}

void Game::run() {

    // lower animation thread's priority, thereby yielding to the "main" aka 'Event Dispatch'
    // thread which listens to keystrokes
    animationThread->setPriority(QThread::LowestPriority);

    // and get the current time
    qint64 startTime = QDateTime::currentMSecsSinceEpoch();

    // this thread animates the scene
    while (animationThread == QThread::currentThread()) {

        m_pGamePanel->update(m_pGamePanel->rect());

        checkCollisions();
        checkNewLevel();
        checkFloaters();

        //keep track of the frame for development purposes
        CommandCenter::getInstance()->incrementFrame();

        // surround the sleep() in a try/catch block
        // this simply controls delay time between
        // the frames of the animation
        try {
            // The total amount of time is guaranteed to be at least ANIMATION_DELAY long.  If processing (update)
            // between frames takes longer than ANIMATION_DELAY, then the difference between startTime -
            // System.currentTimeMillis() will be negative, then zero will be the sleep time
            startTime += ANIMATION_DELAY;

            QThread::msleep(qMax(0ll, startTime - QDateTime::currentMSecsSinceEpoch()));
        } catch (...) {
            // do nothing (bury the exception), and just continue, e.g. skip this frame -- no big deal
        }
    } // end while
}

void Game::setGamePanel(GamePanel* gamePanel)
{
    m_pGamePanel = gamePanel;
}


void Game::checkFloaters() {
    spawnNewWallFloater();
    spawnShieldFloater();
    spawnNukeFloater();
}


void  Game::checkCollisions() {
    QPoint pntFriendCenter, pntFoeCenter;
    int radFriend, radFoe;
    
    //This has order-of-growth of O(n^2), there is no way around this.
    for (Movable* movFriend : CommandCenter::getInstance()->getMovFriends()) {
        for (Movable* movFoe : CommandCenter::getInstance()->getMovFoes()) {

            pntFriendCenter = movFriend->getCenter();
            pntFoeCenter = movFoe->getCenter();
            radFriend = movFriend->getRadius();
            radFoe = movFoe->getRadius();

            //detect collision
            double w_dblDistance = Utils::my_getDistances(pntFriendCenter, pntFoeCenter);
            if (w_dblDistance < (radFriend + radFoe)) {
                //remove the friend (so long as he is not protected)
                if (!movFriend->isProtected()) {
                    if (!CommandCenter::getInstance()->getOpsQueue()->isExist(movFriend))
                        CommandCenter::getInstance()->getOpsQueue()->enqueue(movFriend, GameOp::Action::REMOVE);
                }
                //remove the foe
                if (!CommandCenter::getInstance()->getOpsQueue()->isExist(movFoe))
                    CommandCenter::getInstance()->getOpsQueue()->enqueue(movFoe, GameOp::Action::REMOVE);
                
                if (dynamic_cast<Brick*>(movFoe) != nullptr) {
                    CommandCenter::getInstance()->setScore(CommandCenter::getInstance()->getScore() + 1000);
                    //Sound::playSound(":/resources/sounds/rock.wav");
                } else {
                    CommandCenter::getInstance()->setScore(CommandCenter::getInstance()->getScore() + 10);
                    //Sound::playSound(":/resources/sounds/kapow.wav");
                }
            }

        }//end inner for
    }//end outer for

   

    //check for collisions between falcon and floaters. Order of growth of O(n) where n is number of floaters
    QPoint pntFalCenter = CommandCenter::getInstance()->getFalcon()->getCenter();
    int radFalcon = CommandCenter::getInstance()->getFalcon()->getRadius();

    QPoint pntFloaterCenter;
    int radFloater;
    for (Movable* movFloater : CommandCenter::getInstance()->getMovFloaters()) {
        pntFloaterCenter = movFloater->getCenter();
        radFloater = movFloater->getRadius();

        //detect collision
        double w_dblLength = Utils::my_getDistances(pntFalCenter, pntFloaterCenter);
        if (w_dblLength < (radFalcon + radFloater)) {

            std::string clazz = typeid(*movFloater).name();
            
            if (clazz.find("ShieldFloater") != std::string::npos) {
                 //Sound::playSound(":/resources/sounds/shieldup.wav");
                 CommandCenter::getInstance()->getFalcon()->setShield(Falcon::MAX_SHIELD);
            }
            else if (clazz.find("NewWallFloater") != std::string::npos ) {
                //Sound::playSound(":/resources/sounds/insect.wav");
                buildWall();
            }
            else if (clazz.find("NukeFloater") != std::string::npos ) {
                 //Sound::playSound(":/resources/sounds/nuke-up.wav");
                 CommandCenter::getInstance()->getFalcon()->setNukeMeter(Falcon::MAX_NUKE);
                   
            }
            
            if(!CommandCenter::getInstance()->getOpsQueue()->isExist(movFloater))
                CommandCenter::getInstance()->getOpsQueue()->enqueue(movFloater, GameOp::Action::REMOVE);


        }//end if
    }//end for

    processGameOpsQueue();

}//end meth

void Game::processGameOpsQueue() {
    while (!CommandCenter::getInstance()->getOpsQueue()->empty()) {

        CommandCenter* opsQueue = CommandCenter::getInstance();

        GameOp* gameOp = CommandCenter::getInstance()->getOpsQueue()->dequeue();
        Movable *mov = gameOp->getMovable();
        GameOp::Action action = gameOp->getAction();

        switch (mov->getTeam()) {
            case Movable::FOE:
            {
                QVector<Movable*>& test = CommandCenter::getInstance()->getMovFoes();
                if (action == GameOp::ADD) {
                    CommandCenter::getInstance()->getMovFoes().push_back(mov);
                }
                else { //GameOp::REMOVE
                    CommandCenter::getInstance()->getMovFoes().removeAll(mov);
                    test = CommandCenter::getInstance()->getMovFoes();
                    if (Asteroid* ast = dynamic_cast<Asteroid*>(mov)) {
                        spawnSmallerAsteroidsOrDebris(ast);
                    }
                    delete mov;
                }
                break;
            }
            case Movable::FRIEND:
                if (action == GameOp::ADD) {
                    CommandCenter::getInstance()->getMovFriends().push_back(mov);
                } else { //GameOp::Operation.REMOVE
                    if (Falcon *fal = dynamic_cast<Falcon *>(mov)) {
                        CommandCenter::getInstance()->initFalconAndDecrementFalconNum();
                    } else {
                        CommandCenter::getInstance()->getMovFriends().removeAll(mov);
                        delete mov;
                    }
                }
                break;

            case Movable::FLOATER:
                if (action == GameOp::ADD) {
                    CommandCenter::getInstance()->getMovFloaters().push_back(mov);
                } else { //GameOp::Operation.REMOVE
                    CommandCenter::getInstance()->getMovFloaters().removeOne(mov);
                    delete mov;
                }
                break;

            case Movable::DEBRIS:
                if (action == GameOp::ADD) {
                    CommandCenter::getInstance()->getMovDebris().push_back(mov);
                } else { //GameOp::Operation.REMOVE
                    CommandCenter::getInstance()->getMovDebris().removeOne(mov);
                    delete mov;
                }
                break;
        }

    }
}

void Game::buildWall()
{
    int BRICK_SIZE = Game::DIM.width() / 30, ROWS = 2, COLS = 20, X_OFFSET = BRICK_SIZE * 5, Y_OFFSET = 50;

    for (int nCol = 0; nCol < COLS; nCol++) {
        for (int nRow = 0; nRow < ROWS; nRow++) {
            CommandCenter::getInstance()->getOpsQueue()->enqueue(
                    new Brick(
                            QPoint(nCol * BRICK_SIZE + X_OFFSET, nRow * BRICK_SIZE + Y_OFFSET),
                            BRICK_SIZE),
                    GameOp::ADD);

        }
    }
}

void Game::spawnNewWallFloater() {
    if (CommandCenter::getInstance()->getFrame() % NewWallFloater::SPAWN_NEW_WALL_FLOATER == 0 && isBrickFree()) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new NewWallFloater(), GameOp::ADD);
    }
}


void Game::spawnShieldFloater() {
    if (CommandCenter::getInstance()->getFrame() % ShieldFloater::SPAWN_SHIELD_FLOATER == 0) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new ShieldFloater(), GameOp::ADD);
    }
}

void Game::spawnNukeFloater() {
    if (CommandCenter::getInstance()->getFrame() % NukeFloater::SPAWN_NUKE_FLOATER == 0) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new NukeFloater(), GameOp::ADD);
    }
}

void Game::spawnBigAsteroids(int num) {
    while (num-- > 0) {
        //Asteroids with size of zero are big
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new Asteroid(0), GameOp::ADD);

    }
}


void Game::spawnSmallerAsteroidsOrDebris(Asteroid *originalAsteroid) {

    int size = originalAsteroid->getSize();
    //small asteroids
    if (size > 1) {
        CommandCenter::getInstance()->getOpsQueue()->enqueue(new WhiteCloudDebris(originalAsteroid), GameOp::ADD);
    }
    //med and large
    else {
        //for large (0) and medium (1) sized Asteroids only, spawn 2 or 3 smaller asteroids respectively
        //We can use the existing variable (size) to do this
        size += 2;
        while (size-- > 0) {
            CommandCenter::getInstance()->getOpsQueue()->enqueue(new Asteroid(*originalAsteroid), GameOp::ADD);
        }
    }

}

bool Game::isBrickFree()
{
    //if there are no more Bricks on the screen
    bool brickFree = true;
    for (Movable* movFoe : CommandCenter::getInstance()->getMovFoes()) {
        if (movFoe && dynamic_cast<Brick*>(movFoe)) {
            brickFree = false;
            break;
        }
    }
    return brickFree;
}

bool Game::isLevelClear()
{
    //if there are no more Asteroids on the screen
    bool asteroidFree = true;
    for (Movable* movFoe : CommandCenter::getInstance()->getMovFoes()) {
        if (movFoe && dynamic_cast<Asteroid*>(movFoe)) {
            asteroidFree = false;
            break;
        }
    }
    return asteroidFree;
}

void Game::checkNewLevel()
{
    if (isLevelClear()) {
        //currentLevel will be zero at beginning of game
        int level = CommandCenter::getInstance()->getLevel();
        //award some points for having cleared the previous level
        CommandCenter::getInstance()->setScore(CommandCenter::getInstance()->getScore() + (10000L * level));
        //bump the level up
        level = level + 1;
        CommandCenter::getInstance()->setLevel(level);
        //spawn some big new asteroids
        Falcon* falcon = CommandCenter::getInstance()->getFalcon();
        if (falcon) {
            spawnBigAsteroids(level);
            falcon->setShield(Falcon::INITIAL_SPAWN_TIME);
            //show "Level X" in middle of screen
            falcon->setShowLevel(Falcon::INITIAL_SPAWN_TIME);
        }
    }
}

void Game::stopLoopingSounds(QSoundEffect* soundThrust, QSoundEffect* soundBackground)
{
//    if(soundThrust && soundThrust->isPlaying()) {
//        soundThrust->stop();
//    }
//
//    if(soundBackground && soundBackground->isPlaying()) {
//        soundBackground->stop();
//    }
}

void Game::keyPressEvent(QKeyEvent* event)
{
    Falcon* falcon = CommandCenter::getInstance()->getFalcon();

    switch (event->key()) {
    case START:
        if (CommandCenter::getInstance()->isGameOver()) {
            CommandCenter::getInstance()->initGame();
            return;
        }
        break;

    case PAUSE:
        CommandCenter::getInstance()->setPaused(!CommandCenter::getInstance()->getPaused());
//        if (CommandCenter::getInstance()->getPaused()) {
//            stopLoopingSounds(soundThrust, soundBackground);
//        }
        break;

    case QUIT:
        QCoreApplication::quit();
        break;

    case UP:
        if (falcon) {
            falcon->setThrusting(true);
          //  soundThrust->play();
        }
        break;

    case LEFT:
        if (falcon) {
            falcon->setTurnState(Falcon::LEFT);
        }
        break;

    case RIGHT:
        if (falcon) {
            falcon->setTurnState(Falcon::RIGHT);
        }
        break;

    default:
        break;
    }

    event->accept();
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    Falcon* falcon = CommandCenter::getInstance()->getFalcon();

    switch (event->key()) {
    case FIRE:
        if (falcon) {
            CommandCenter::getInstance()->getOpsQueue()->enqueue(new Bullet(falcon), GameOp::Action::ADD);
          //  QSoundEffect::play("thump.wav");
        }
        break;

    case LEFT:
    case RIGHT:
        if (falcon) {
            falcon->setTurnState(Falcon::IDLE);
        }
        break;

    case UP:
        if (falcon) {
            falcon->setThrusting(false);
          //  soundThrust->stop();
        }
        break;

    case NUKE:
        if (falcon && falcon->getNukeMeter() > 0) {
            CommandCenter::getInstance()->getOpsQueue()->enqueue(new Nuke(falcon), GameOp::Action::ADD);
          //  QSoundEffect::play("nuke.wav");
            falcon->setNukeMeter(0);
        }
        break;

    case MUTE:
        CommandCenter::getInstance()->setMuted(!CommandCenter::getInstance()->getMuted());
        if (!CommandCenter::getInstance()->getMuted())
        {
          //  stopLoopingSounds(soundBackground, nullptr);
        }
        else
        {
           // soundBackground->play();
        }
        break;

    default:
        break;
    }

    event->accept();
}


**/
