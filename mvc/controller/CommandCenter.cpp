#include "CommandCenter.h"
#include "Game.h"
#include <climits>

CommandCenter* CommandCenter::instance = nullptr;

CommandCenter::CommandCenter()
    :numFalcons(0), level(0), score(0), paused(false), muted(false), frame(0), falcon(std::make_shared<Falcon>())
{
    for (int i = 0; i < 5; ++i) {
        soundThreads.emplace_back(&CommandCenter::soundThreadWorker, this);
    }

    miniMap = std::make_shared<MiniMap>();
    setRadar(true);
}

CommandCenter::~CommandCenter()
{
    terminateSoundThreads = true;
    soundCondVar.notify_all();
    for (auto& thread : soundThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void CommandCenter::soundThreadWorker()
{
    while (!terminateSoundThreads) {
        std::unique_lock<std::mutex> lock(soundMutex);
        soundCondVar.wait(lock, [this] { return !soundQueue.empty() || terminateSoundThreads; });
        if (terminateSoundThreads) break;
        std::string sound = soundQueue.front();
        soundQueue.pop();
        lock.unlock();
        Sound::instance()->playSound(sound);
    }
}

CommandCenter *CommandCenter::getInstance()
{
    if (instance == nullptr) {
        instance = new CommandCenter();
    }
    return instance;
}

void CommandCenter::setDimHash() {
    miniDimHash[Universe::FREE_FLY] = sf::Vector2u(1, 1);
    miniDimHash[Universe::CENTER] = sf::Vector2u(1, 1);
    miniDimHash[Universe::BIG] = sf::Vector2u(2, 2);
    miniDimHash[Universe::HORIZONTAL] = sf::Vector2u(3, 1);
    miniDimHash[Universe::VERTICAL] = sf::Vector2u(1, 3);
    miniDimHash[Universe::DARK] = sf::Vector2u(4, 4);
}

void CommandCenter::initGame()
{
    clearAll();
    generateStarField();
    setDimHash();
    level = 0;
    score = 0;
    paused = false;
    numFalcons = 4;
    initFalconAndDecrementFalconNum();
    opsQueue.enqueue(falcon, GameOp::Action::ADD);
    opsQueue.enqueue(miniMap, GameOp::Action::ADD);
}

void CommandCenter::generateStarField()
{
    int count = 100;
    while (count-- > 0) {
        opsQueue.enqueue(std::make_shared<Star>(), GameOp::Action::ADD);
    }
}

void CommandCenter::initFalconAndDecrementFalconNum()
{
    numFalcons--;
    if (isGameOver()) return;
    soundQueue.push("shipspawn.wav");
    soundCondVar.notify_one();
    falcon->setShield(Falcon::INITIAL_SPAWN_TIME);
    falcon->setInvisible(Falcon::INITIAL_SPAWN_TIME / 4);
    falcon->setCenter(sf::Vector2f(Game::DIM.x / 2, Game::DIM.y / 2));
    falcon->setOrientation(Game::nextInt(360 / Falcon::TURN_STEP) * Falcon::TURN_STEP);
    falcon->setDeltaX(0);
    falcon->setDeltaY(0);
    falcon->setRadius(Falcon::MIN_RADIUS);
    falcon->setMaxSpeedAttained(false);
    falcon->setNukeMeter(0);
}

void CommandCenter::incrementFrame()
{
    frame = frame < LONG_MAX ? frame + 1 : 0;
}

void CommandCenter::clearAll()
{
    movDebris.clear();
    movFriends.clear();
    movFoes.clear();
    movFloaters.clear();
}

bool CommandCenter::isGameOver() const
{
    return numFalcons < 1;
}

Falcon *CommandCenter::getFalcon() const
{
    return falcon.get();
}

sf::Vector2u CommandCenter::getUniDim() const
{
    auto it = miniDimHash.find(universe);
    if (it != miniDimHash.end()) {
        return it->second;
    }
    // Default dimension if universe is not found
    return sf::Vector2u(800, 600);
}
