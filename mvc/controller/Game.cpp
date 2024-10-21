#include "Game.h"
#include "Asteroid.h"

const sf::Vector2u Game::DIM(1100, 900);
std::mt19937 Game::R(std::random_device{}());


const int Game::FRAMES_PER_SECOND()
{
    const int FPS = 1000 / ANIMATION_DELAY;
    return FPS;
}

void Game::run()
{
    while (isRunning && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed" << std::endl;
                handleInput(event);
            } else if (event.type == sf::Event::KeyReleased) {
                std::cout << "Key pressed" << std::endl;
                handleInput(event, true);
            }
        }
        //handleInput();
        gamePanel.update();

        CommandCenter::getInstance()->incrementFrame();

        // Control frame rate
        sf::sleep(sf::milliseconds(ANIMATION_DELAY));
    }
}

void Game::runAnimations()
{
    while (isRunning && window.isOpen()) {
        checkCollisions();
        checkNewLevel();
        checkFloaters();

        CommandCenter::getInstance()->incrementFrame();

        // Control frame rate
        sf::sleep(sf::milliseconds(ANIMATION_DELAY));
    }
}

void Game::handleInput(const sf::Event &event, bool isReleased)
{
    Falcon* falcon = CommandCenter::getInstance()->getFalcon();


    // Handle discrete actions (one-time events)
    switch (event.key.code)
    {
    case sf::Keyboard::P: {
        CommandCenter::getInstance()->setPaused(!CommandCenter::getInstance()->isPaused());
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
        }
        break;
    }
    case sf::Keyboard::Up: {
        if (!isReleased) {
            falcon->setThrusting(true);
            soundThrust.setLoop(true);
            soundThrust.play();
        } else {
            falcon->setThrusting(false);
            soundThrust.stop();
        }
        break;
    }
    case sf::Keyboard::Left: {
        if (isReleased) {
            falcon->setTurnState(Falcon::TurnState::IDLE);
        } else {
            falcon->setTurnState(Falcon::TurnState::LEFT);
        }
        break;
    }
    case sf::Keyboard::Right: {
        if (isReleased) {
            falcon->setTurnState(Falcon::TurnState::IDLE);
        } else {
            falcon->setTurnState(Falcon::TurnState::RIGHT);
        }
        break;
    }
    case sf::Keyboard::Down: {

    }
    }


}

void Game::checkCollisions()
{
    for (auto& movFriend : CommandCenter::getInstance()->getMovFriends()) {
        for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
            if ( getDistance(movFriend->getCenter(), movFoe->getCenter()) < (movFriend->getRadius() + movFoe->getRadius())) {
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
        if ( getDistance(falcon->getCenter(), movFloater->getCenter()) < (falcon->getRadius() + movFloater->getRadius())) {
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

void Game::checkNewLevel()
{
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

void Game::processGameOpsQueue()
{
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

void Game::buildWall()
{
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

void Game::spawnNewWallFloater()
{
    if (CommandCenter::getInstance()->getFrame() % NewWallFloater::SPAWN_NEW_WALL_FLOATER() == 0 && isBrickFree()) {
        CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<NewWallFloater>(), GameOp::Action::ADD);
    }
}

void Game::spawnShieldFloater()
{
    if (CommandCenter::getInstance()->getFrame() % ShieldFloater::SPAWN_SHIELD_FLOATER() == 0) {
        CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<ShieldFloater>(), GameOp::Action::ADD);
    }
}

void Game::spawnNukeFloater()
{
    if (CommandCenter::getInstance()->getFrame() % NukeFloater::SPAWN_NUKE_FLOATER == 0) {
        CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<NukeFloater>(), GameOp::Action::ADD);
    }
}

void Game::spawnBigAsteroids(int num)
{
    while (num-- > 0) {
        CommandCenter::getInstance()->getOpsQueue().enqueue(std::make_shared<Asteroid>(0), GameOp::Action::ADD);
    }
}

bool Game::isBrickFree()
{
    for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
        if (dynamic_cast<Brick*>(movFoe.get())) {
            return false;
        }
    }
    return true;
}

bool Game::isLevelClear()
{
    for (auto& movFoe : CommandCenter::getInstance()->getMovFoes()) {
        if (dynamic_cast<Asteroid*>(movFoe.get())) {
            return false;
        }
    }
    return true;
}
