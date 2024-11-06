#include "Game.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "Nuke.h"
#include "collisions.h"

const sf::Vector2u Game::DIM(1100, 900);
std::mt19937 Game::R(std::random_device{}());

Game::Game()
    : window(sf::VideoMode(1100, 900), "Asteroid"),
      gamePanel(window, this),
      isRunning(true),
      animationThread(&Game::runAnimations, this),
      gameStarted(false) {
  // Load sounds
  thrustBuffer.loadFromFile(sound_files_path + "whitenoise.wav");
  backgroundBuffer.loadFromFile(sound_files_path + "music-background.wav");
  soundThrust.setBuffer(thrustBuffer);
  soundBackground.setBuffer(backgroundBuffer);

  // Start the animation thread
  animationThread.launch();
}

const int Game::FRAMES_PER_SECOND() {
  const int FPS = 1000 / ANIMATION_DELAY;
  return FPS;
}

void Game::run() {
  while (isRunning && window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        std::cout << "Key pressed" << std::endl;
        handlekeyPressed(event);
      } else if (event.type == sf::Event::KeyReleased) {
        std::cout << "Key pressed" << std::endl;
        handlekeyRelease(event);
      }
    }
    // handleInput();
    window.clear();
    gamePanel.update();

    CommandCenter::getInstance()->incrementFrame();

    // Control frame rate
    sf::sleep(sf::milliseconds(ANIMATION_DELAY));
  }
}

void Game::runAnimations() {
  while (isRunning && window.isOpen()) {
    checkCollisions();
    checkNewLevel();
    CommandCenter::getInstance()->incrementFrame();
    // Control frame rate
    sf::sleep(sf::milliseconds(ANIMATION_DELAY));
  }
}

void Game::handlekeyPressed(const sf::Event& event) {
  Falcon* falcon = CommandCenter::getInstance()->getFalcon();

  // Handle discrete actions (one-time events)
  switch (event.key.code) {
    case sf::Keyboard::P: {
      CommandCenter::getInstance()->setPaused(
          !CommandCenter::getInstance()->isPaused());
      if (CommandCenter::getInstance()->isPaused()) {
        stopLoopingSounds(soundBackground, soundThrust);
      }
      break;
    }
    case sf::Keyboard::Q: {
      window.close();
      break;
    }
    case sf::Keyboard::S: {
      if (CommandCenter::getInstance()->isGameOver()) {
        CommandCenter::getInstance()->initGame();
        gameStarted = true;
      }
      break;
    }
    case sf::Keyboard::Up: {
      falcon->setThrusting(true);
      soundThrust.setLoop(true);
      soundThrust.play();
      break;
    }
    case sf::Keyboard::Left: {
      falcon->setTurnState(Falcon::TurnState::LEFT);
      break;
    }
    case sf::Keyboard::Right: {
      falcon->setTurnState(Falcon::TurnState::RIGHT);
      break;
    }
  }
}

/**
    private static final int
            PAUSE = 80, // p key
            QUIT = 81, // q key
            LEFT = 37, // rotate left; left arrow
            RIGHT = 39, // rotate right; right arrow
            UP = 38, // thrust; up arrow
            START = 83, // s key
            FIRE = 32, // space key
            MUTE = 77, // m-key mute

            NUKE = 78; // n-key mute
 */

void Game::handlekeyRelease(const sf::Event& event) {
  CommandCenter* cm = CommandCenter::getInstance();
  Falcon* falcon = cm->getFalcon();

  // Handle discrete actions (one-time events)
  switch (event.key.code) {
    case sf::Keyboard::Space: {
      std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(*falcon);
      cm->getOpsQueue().enqueue(bullet, GameOp::Action::ADD);
      break;
    }
    case sf::Keyboard::P: {
      CommandCenter::getInstance()->setPaused(
          !CommandCenter::getInstance()->isPaused());
      if (CommandCenter::getInstance()->isPaused()) {
        stopLoopingSounds(soundBackground, soundThrust);
      }
      break;
    }
    case sf::Keyboard::N: {
      if (falcon->getNukeMeter() > 0) {
        std::shared_ptr<Nuke> nuke = std::make_shared<Nuke>(*falcon);
        cm->getOpsQueue().enqueue(nuke, GameOp::Action::ADD);
        Sound::instance()->playSound(SOUND_NUKE);
        falcon->setNukeMeter(0);
      }
    }
    case sf::Keyboard::Up: {
      falcon->setThrusting(false);
      soundThrust.stop();
      break;
    }
    case sf::Keyboard::Left:
    case sf::Keyboard::Right: {
      falcon->setTurnState(Falcon::TurnState::IDLE);
      break;
    }
    case sf::Keyboard::Down: {
    }
  }
}

void Game::checkCollisions() {
  for (auto& movFriend : CommandCenter::getInstance()->getMovFriends()) {
    for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
      Collisions collision{movFriend, movFoe};
      if (collision.intersect()) {
        if (!movFriend->isProtected()) {
          CommandCenter::getInstance()->getOpsQueue().enqueue(
              movFriend, GameOp::Action::REMOVE);
        }
        CommandCenter::getInstance()->getOpsQueue().enqueue(
            movFoe, GameOp::Action::REMOVE);

        CommandCenter::getInstance()->setScore(
            CommandCenter::getInstance()->getScore() + 10);
        Sound::instance()->playSound(SOUND_KAPOW);
      }
    }
  }

  auto falcon = CommandCenter::getInstance()->getFalcon();
  for (auto& movFloater : CommandCenter::getInstance()->getMovFloaters()) {
    if (getDistance(falcon->getCenter(), movFloater->getCenter()) <
        (falcon->getRadius() + movFloater->getRadius())) {
      if (dynamic_cast<ShieldFloater*>(movFloater.get())) {
        Sound::instance()->playSound(SOUND_SHIELD_UP);
        falcon->setShield(Falcon::MAX_SHIELD);
      } else if (dynamic_cast<NukeFloater*>(movFloater.get())) {
        Sound::instance()->playSound(SOUND_NUKE_UP);
        falcon->setNukeMeter(Falcon::MAX_NUKE);
      }
      CommandCenter::getInstance()->getOpsQueue().enqueue(
          movFloater, GameOp::Action::REMOVE);
    }
  }

  processGameOpsQueue();
}

void Game::checkNewLevel() {
  if (isLevelClear()) {
    int level = CommandCenter::getInstance()->getLevel();
    CommandCenter::getInstance()->setScore(
        CommandCenter::getInstance()->getScore() + (10000 * level));
    level++;
    CommandCenter::getInstance()->setLevel(level);
    auto falcon = CommandCenter::getInstance()->getFalcon();
    if (falcon) {
      spawnBigAsteroids(level);
      falcon->setShield(Falcon::INITIAL_SPAWN_TIME);
      falcon->setShowLevel(Falcon::INITIAL_SPAWN_TIME);
    }
  }
}

void Game::checkFloaters() {
  spawnShieldFloater();
  spawnNukeFloater();
}

void Game::processGameOpsQueue() {
  CommandCenter* cm = CommandCenter::getInstance();
  while (!cm->getOpsQueue().isEmpty()) {
    GameOp gameOp = CommandCenter::getInstance()->getOpsQueue().dequeue();
    std::shared_ptr<Movable> mov = gameOp.getMovable();
    GameOp::Action action = gameOp.getAction();
    Movable::Team team = mov->getTeam();
    switch (team) {
      case Movable::Team::FOE:
        if (action == GameOp::Action::ADD) {
          CommandCenter::getInstance()->getMovFoes().push_back(mov);
        } else {
          auto vec = cm->getMovFoes();
          CommandCenter::getInstance()->getMovFoes().remove(mov);
          if (auto ast = std::dynamic_pointer_cast<Asteroid>(mov)) {
            spawnSmallerAsteroidsOrDebris(ast);
          }
          mov.reset();
        }
        break;
      case Movable::Team::FRIEND:
        if (action == GameOp::Action::ADD) {
          CommandCenter::getInstance()->getMovFriends().push_back(mov);
        } else {
          if (auto fal = std::dynamic_pointer_cast<Falcon>(mov)) {
            cm->initFalconAndDecrementFalconNum();
          } else {
            CommandCenter::getInstance()->getMovFriends().remove(mov);
          }
        }
        break;
      case Movable::Team::FLOATER:
        if (action == GameOp::Action::ADD) {
          CommandCenter::getInstance()->getMovFloaters().push_back(mov);
        } else {
          CommandCenter::getInstance()->getMovFloaters().remove(mov);
        }
        break;
      case Movable::Team::DEBRIS:
        if (action == GameOp::Action::ADD) {
          CommandCenter::getInstance()->getMovDebris().push_back(mov);
        } else {
          CommandCenter::getInstance()->getMovDebris().remove(mov);
        }
        break;
    }
  }
}

void Game::spawnShieldFloater() {
  if (CommandCenter::getInstance()->getFrame() %
          ShieldFloater::SPAWN_SHIELD_FLOATER() ==
      0) {
    CommandCenter::getInstance()->getOpsQueue().enqueue(
        std::make_shared<ShieldFloater>(), GameOp::Action::ADD);
  }
}

void Game::spawnNukeFloater() {
  if (CommandCenter::getInstance()->getFrame() %
          NukeFloater::SPAWN_NUKE_FLOATER ==
      0) {
    CommandCenter::getInstance()->getOpsQueue().enqueue(
        std::make_shared<NukeFloater>(), GameOp::Action::ADD);
  }
}

void Game::spawnSmallerAsteroidsOrDebris(
    std::shared_ptr<Asteroid> originalAsteroid) {
  int size = originalAsteroid->getSize();
  // small asteroids
  if (size > 1) {
    auto wcd = std::make_shared<WhiteCloudDebris>(originalAsteroid.get());
    CommandCenter::getInstance()->getOpsQueue().enqueue(wcd,
                                                        GameOp::Action::ADD);
  }
  // med and large
  else {
    // for large (0) and medium (1) sized Asteroids only, spawn 2 or 3 smaller
    // asteroids respectively We can use the existing variable (size) to do this
    size += 2;
    while (size-- > 0) {
      auto ast = std::make_shared<Asteroid>(*originalAsteroid);
      CommandCenter::getInstance()->getOpsQueue().enqueue(ast,
                                                          GameOp::Action::ADD);
    }
  }
}

void Game::spawnBigAsteroids(int num) {
  while (num-- > 0) {
    auto ast = std::make_shared<Asteroid>(0);
    CommandCenter::getInstance()->getOpsQueue().enqueue(ast,
                                                        GameOp::Action::ADD);
  }
}

bool Game::isLevelClear() {
  CommandCenter* cm = CommandCenter::getInstance();
  for (auto& movFoe : cm->getMovFoes()) {
    if (dynamic_cast<Asteroid*>(movFoe.get())) {
      return false;
    }
  }
  return true;
}
