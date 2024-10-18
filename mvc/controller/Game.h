#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "CommandCenter.h"
#include "Sound.h"
#include "GamePanel.h"
#include "Asteroid.h"
#include "Movable.h"
#include "Brick.h"

#include "Falcon.h"
#include "GameOp.h"
#include "ShieldFloater.h"
#include "NewWallFloater.h"
#include "WhiteCloudDebris.h"
#include "GamePanel.h"

class Game {
public:
    Game() :
        window(sf::VideoMode(1100, 900), "MVC Game - SFML"),
        gamePanel(window),
        isRunning(true),
        animationThread(&Game::run, this)
    {
        // Load sounds
        thrustBuffer.loadFromFile("whitenoise.wav");
        backgroundBuffer.loadFromFile("music-background.wav");
        soundThrust.setBuffer(thrustBuffer);
        soundBackground.setBuffer(backgroundBuffer);

        // Start the animation thread
        animationThread.launch();
    }

    void run() {
        while (isRunning && window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            handleInput();
            gamePanel.update();
            checkCollisions();
            checkNewLevel();
            checkFloaters();

            CommandCenter::getInstance()->incrementFrame();

            // Control frame rate
            sf::sleep(sf::milliseconds(ANIMATION_DELAY));
        }
    }

private:
    static const int ANIMATION_DELAY = 40;
    sf::RenderWindow window;
    GamePanel gamePanel;
    sf::SoundBuffer thrustBuffer, backgroundBuffer;
    sf::Sound soundThrust, soundBackground;
    sf::Thread animationThread;
    bool isRunning;

    void handleInput() {
        Falcon* falcon = CommandCenter::getInstance()->getFalcon();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            CommandCenter::getInstance()->setPaused(!CommandCenter::getInstance()->isPaused());
            if (CommandCenter::getInstance()->isPaused()) {
                stopLoopingSounds(soundBackground, soundThrust);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            falcon->setThrusting(true);
            soundThrust.setLoop(true);
            soundThrust.play();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            falcon->setTurnState(Falcon::TurnState::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            falcon->setTurnState(Falcon::TurnState::RIGHT);
        }
    }

    void checkCollisions() {
        for (auto& movFriend : CommandCenter::getInstance()->getMovFriends()) {
            for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
                if (movFriend->getCenter().distance(movFoe->getCenter()) < (movFriend->getRadius() + movFoe->getRadius())) {
                    if (!movFriend->isProtected()) {
                        CommandCenter::getInstance()->getOpsQueue().enqueue(movFriend, GameOp::Action::REMOVE);
                    }
                    CommandCenter::getInstance()->getOpsQueue().enqueue(movFoe, GameOp::Action::REMOVE);

                    if (dynamic_cast<Brick*>(movFoe.get())) {
                        CommandCenter::getInstance()->setScore(CommandCenter::getInstance()->getScore() + 1000);
                        Sound::instance()->playSound("rock.wav");
                    } else {
                        CommandCenter::getInstance()->setScore(CommandCenter::getInstance()->getScore() + 10);
                        Sound::instance()->playSound("kapow.wav");
                    }
                }
            }
        }

        auto falcon = CommandCenter::getInstance()->getFalcon();
        for (auto& movFloater : CommandCenter::getInstance()->getMovFloaters()) {
            if (falcon->getCenter().distance(movFloater->getCenter()) < (falcon->getRadius() + movFloater->getRadius())) {
                if (dynamic_cast<ShieldFloater*>(movFloater.get())) {
                    Sound::instance()->playSound("shieldup.wav");
                    falcon->setShield(Falcon::MAX_SHIELD);
                } else if (dynamic_cast<NewWallFloater*>(movFloater.get())) {
                    Sound::instance()->playSound("insect.wav");
                    buildWall();
                } else if (dynamic_cast<NukeFloater*>(movFloater.get())) {
                    Sound::instance()->playSound("nuke-up.wav");
                    falcon->setNukeMeter(Falcon::MAX_NUKE);
                }
                CommandCenter::getInstance()->getOpsQueue().enqueue(movFloater, GameOp::Action::REMOVE);
            }
        }

        processGameOpsQueue();
    }

    void checkNewLevel() {
        if (isLevelClear()) {
            int level = CommandCenter::getInstance()->getLevel();
            CommandCenter::getInstance()->setScore(CommandCenter::getInstance()->getScore() + (10000 * level));
            level++;
            CommandCenter::getInstance()->setLevel(level);
            spawnBigAsteroids(level);
            auto falcon = CommandCenter::getInstance()->getFalcon();
            falcon->setShield(Falcon::INITIAL_SPAWN_TIME);
            falcon->setShowLevel(Falcon::INITIAL_SPAWN_TIME);
        }
    }

    void checkFloaters() {
        spawnNewWallFloater();
        spawnShieldFloater();
        spawnNukeFloater();
    }

    void processGameOpsQueue() {
        while (!CommandCenter::getInstance()->getOpsQueue().isEmpty()) {
            GameOp gameOp = CommandCenter::getInstance()->getOpsQueue().dequeue();
            auto mov = gameOp.getMovable();
            auto action = gameOp.getAction();
            switch (mov->getTeam()) {
            case Movable::Team::FOE:
                action == GameOp::Action::ADD ? CommandCenter::getInstance()->getMovFoes().push_back(mov)
                                              : CommandCenter::getInstance()->getMovFoes().remove(mov);
                break;
            case Movable::Team::FRIEND:
                action == GameOp::Action::ADD ? CommandCenter::getInstance()->getMovFriends().push_back(mov)
                                              : CommandCenter::getInstance()->getMovFriends().remove(mov);
                break;
            case Movable::Team::FLOATER:
                action == GameOp::Action::ADD ? CommandCenter::getInstance()->getMovFloaters().push_back(mov)
                                              : CommandCenter::getInstance()->getMovFloaters().remove(mov);
                break;
            case Movable::Team::DEBRIS:
                action == GameOp::Action::ADD ? CommandCenter::getInstance()->getMovDebris().push_back(mov)
                                              : CommandCenter::getInstance()->getMovDebris().remove(mov);
                break;
            }
        }
    }

    void buildWall() {
        const int BRICK_SIZE = 1100 / 30, ROWS = 2, COLS = 20, X_OFFSET = BRICK_SIZE * 5, Y_OFFSET = 50;
        for (int nCol = 0; nCol < COLS; nCol++) {
            for (int nRow = 0; nRow < ROWS; nRow++) {
                CommandCenter::getInstance()->getOpsQueue().enqueue(
                    std::make_shared<Brick>(sf::Vector2f(nCol * BRICK_SIZE + X_OFFSET, nRow * BRICK_SIZE + Y_OFFSET), BRICK_SIZE),
                    GameOp::Action::ADD
                    );
            }
        }
    }

    void spawnNewWallFloater() {
        if (CommandCenter::getInstance()->getFrame() % NewWallFloater::SPAWN_NEW_WALL_FLOATER == 0 && isBrickFree()) {
            CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<NewWallFloater>(), GameOp::Action::ADD);
        }
    }

    void spawnShieldFloater() {
        if (CommandCenter::getInstance()->getFrame() % ShieldFloater::SPAWN_SHIELD_FLOATER == 0) {
            CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<ShieldFloater>(), GameOp::Action::ADD);
        }
    }

    void spawnNukeFloater() {
        if (CommandCenter::getInstance()->getFrame() % NukeFloater::SPAWN_NUKE_FLOATER == 0) {
            CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<NukeFloater>(), GameOp::Action::ADD);
        }
    }

    void spawnBigAsteroids(int num) {
        while (num-- > 0) {
            CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<Asteroid>(0), GameOp::Action::ADD);
        }
    }

    static void stopLoopingSounds(sf::Sound& sound1, sf::Sound& sound2) {
        sound1.stop();
        sound2.stop();
    }

    bool isBrickFree() {
        for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
            if (dynamic_cast<Brick*>(movFoe.get())) {
                return false;
            }
        }
        return true;
    }

    bool isLevelClear() {
        for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
            if (dynamic_cast<Asteroid*>(movFoe.get())) {
                return false;
            }
        }
        return true;
    }
};

#endif
