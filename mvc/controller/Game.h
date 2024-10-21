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
#include "NukeFloater.h"
#include <random>

class Game {
public:
    Game() :
        window(sf::VideoMode(1100, 900), "Asteroid"),
        gamePanel(window),
        isRunning(true),
        animationThread(&Game::runAnimations, this)
    {
        // Load sounds
        thrustBuffer.loadFromFile("whitenoise.wav");
        backgroundBuffer.loadFromFile("music-background.wav");
        soundThrust.setBuffer(thrustBuffer);
        soundBackground.setBuffer(backgroundBuffer);

        // Start the animation thread
        animationThread.launch();
    }

    static std::mt19937 R;
    static int nextInt(int bound) {
        std::uniform_int_distribution<int> dist(0, bound - 1);
        return dist(R);
    }
    static const int FRAMES_PER_SECOND();

    void run();
    void runAnimations();

    static const sf::Vector2u DIM;

private:
    static const int ANIMATION_DELAY = 40;
    sf::RenderWindow window;
    GamePanel gamePanel;
    sf::SoundBuffer thrustBuffer, backgroundBuffer;
    sf::Sound soundThrust, soundBackground;
    sf::Thread animationThread;
    bool isRunning;

    float getDistance(const sf::Vector2<float> vec1, const sf::Vector2<float> vec2)
    {
        sf::Vector2f diff = vec1 - vec2;
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        return distance;
    }

    void handleInput(const sf::Event &event, bool isReleased = false);

    void checkCollisions();

    void checkNewLevel();

    void checkFloaters() {
        spawnNewWallFloater();
        spawnShieldFloater();
        spawnNukeFloater();
    }

    void processGameOpsQueue();

    void buildWall();

    void spawnNewWallFloater();

    void spawnShieldFloater();

    void spawnNukeFloater();

    void spawnBigAsteroids(int num);

    static void stopLoopingSounds(sf::Sound& sound1, sf::Sound& sound2) {
        sound1.stop();
        sound2.stop();
    }

    bool isBrickFree();

    bool isLevelClear();
};

#endif
