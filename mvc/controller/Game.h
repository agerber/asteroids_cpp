#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "CommandCenter.h"
#include "Falcon.h"
#include "GameOp.h"
#include "GamePanel.h"
#include "Movable.h"
#include "NukeFloater.h"
#include "ShieldFloater.h"
#include "Sound.h"
#include "WhiteCloudDebris.h"

class Asteroid;
class Game {
 public:
  Game();

  static std::mt19937 R;
  static int nextInt(int bound) {
    std::uniform_int_distribution<int> dist(0, bound - 1);
    return dist(R);
  }
  static const int FRAMES_PER_SECOND();

  void run();
  void runAnimations();

  static const sf::Vector2u DIM;
  sf::View miniMapView() const { return miniMapView_; }
  sf::RectangleShape miniMapBackground() const { return miniMapBackground_; }

 private:
  static const int ANIMATION_DELAY = 40;
  sf::RenderWindow window;
  GamePanel gamePanel;
  sf::SoundBuffer thrustBuffer, backgroundBuffer;
  sf::Sound soundThrust, soundBackground;
  sf::Thread animationThread;
  bool isRunning;
  bool gameStarted;
  sf::View miniMapView_;
  sf::RectangleShape miniMapBackground_;

  float getDistance(const sf::Vector2<float> vec1,
                    const sf::Vector2<float> vec2) {
    sf::Vector2f diff = vec1 - vec2;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    return distance;
  }

  void handlekeyPressed(const sf::Event& event);
  void handlekeyRelease(const sf::Event& event);

  void checkCollisions();

  void checkNewLevel();

  void checkFloaters();

  void processGameOpsQueue();

  void buildWall();

  void spawnNewWallFloater();

  void spawnShieldFloater();

  void spawnNukeFloater();

  void spawnSmallerAsteroidsOrDebris(
      std::shared_ptr<Asteroid> originalAsteroid);
  void spawnBigAsteroids(int num);

  static void stopLoopingSounds(sf::Sound& sound1, sf::Sound& sound2) {
    sound1.stop();
    sound2.stop();
  }

  bool isBrickFree();

  bool isLevelClear();
};

#endif
