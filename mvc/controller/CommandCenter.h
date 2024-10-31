#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "Falcon.h"
#include "GameOpsQueue.h"
#include "Star.h"
#include "Sound.h"

class CommandCenter {
private:
    int numFalcons;
    int level;
    long score;
    bool paused;
    bool muted;
    std::atomic<long> frame;

    std::shared_ptr<Falcon> falcon;
    std::list<std::shared_ptr<Movable>> movDebris;
    std::list<std::shared_ptr<Movable>> movFriends;
    std::list<std::shared_ptr<Movable>> movFoes;
    std::list<std::shared_ptr<Movable>> movFloaters;

    GameOpsQueue opsQueue;
    std::vector<std::thread> soundThreads;
    std::queue<std::string> soundQueue;
    std::mutex soundMutex;
    std::condition_variable soundCondVar;
    bool terminateSoundThreads = false;

    static CommandCenter* instance;

    // Private constructor for Singleton pattern
    CommandCenter();

    ~CommandCenter();

    // Worker thread for playing sounds
    void soundThreadWorker();

public:
    std::list<std::shared_ptr<Movable>>& getMovFoes() { return movFoes; }
    std::list<std::shared_ptr<Movable>>& getMovFriends() { return movFriends; }
    std::list<std::shared_ptr<Movable>>& getMovFloaters() { return movFloaters; }
    std::list<std::shared_ptr<Movable>>& getMovDebris() { return movDebris; }

    // Get the singleton instance
    static CommandCenter* getInstance();

    void initGame();
    void generateStarField();
    void initFalconAndDecrementFalconNum();
    void incrementFrame();
    void clearAll();
    bool isGameOver() const;

    // Getters and Setters
    int getNumFalcons() const { return numFalcons; }
    void setNumFalcons(int n) { numFalcons = n; }
    int getLevel() const { return level; }
    void setLevel(int l) { level = l; }
    long getScore() const { return score; }
    void setScore(long s) { score = s; }
    bool isPaused() const { return paused; }
    void setPaused(bool p) { paused = p; }
    bool isMuted() const { return muted; }
    void setMuted(bool m) { muted = m; }
    long getFrame() const { return frame; }
    Falcon* getFalcon() const;
    GameOpsQueue& getOpsQueue() { return opsQueue; }
};



#endif
