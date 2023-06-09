//commandcenter.cpp

#include "CommandCenter.h"
#include "Falcon.h"
#include "Star.h"
#include "Game.h"
#include "Sound.h"
#include <QThreadPool>
#include <QDebug>


CommandCenter* CommandCenter::getInstance()
{
    static CommandCenter instance;
    return &instance;
}

void CommandCenter::initGame()
{
    //clear all movables
    clearAll();

    generateStarField();
    //initialize game state
    setLevel(0);
    setScore(0);
    setPaused(false);
    setNumFalcons(4);
    initFalconAndDecrementFalconNum();

    //add the falcon to the movFriends list
    //addOp(GameOp(falcon, GameOp::ADD));
    addOp(GameOp(falcon, GameOp::ADD));

}

void CommandCenter::incrementFrame()
{
    //use of ternary expression to simplify the logic to one line
    frame = frame < LONG_MAX ? frame + 1 : 0;
}

void CommandCenter::initFalconAndDecrementFalconNum()
{
    numFalcons--;

    if (isGameOver()) return;

    //Sound::playSound(":/resources/sounds/shipspawn.wav");
    falcon->setShield(Falcon::INITIAL_SPAWN_TIME);
    falcon->setInvisible(Falcon::INITIAL_SPAWN_TIME/4);
  		//put falcon in the middle of the game-space
	falcon->setCenter(QPoint(Game::DIM.width() / 2, Game::DIM.height() / 2));
	//random number between 0-360 in steps of TURN_STEP
	falcon->setOrientation(QRandomGenerator::global()->bounded(360 / Falcon::TURN_STEP) * Falcon::TURN_STEP);
	falcon->setDeltaX(0);
	falcon->setDeltaY(0);
	falcon->setRadius(Falcon::MIN_RADIUS);
	falcon->setMaxSpeedAttained(false);
	falcon->setNukeMeter(0);
}

void CommandCenter::addOp(GameOp op)
{
    opsQueue->enqueue(op);
}

GameOp* CommandCenter::getOp()
{
    return opsQueue->dequeue();
}

int CommandCenter::getNumFalcons() const
{
    return numFalcons;
}

void CommandCenter::setNumFalcons(int value)
{
    numFalcons = value;
}

int CommandCenter::getLevel() const
{
    return level;
}

void CommandCenter::setLevel(int value)
{
    level = value;
}

long CommandCenter::getScore() const
{
    return score;
}

void CommandCenter::setScore(long value)
{
    score = value;
}

bool CommandCenter::getPaused() const
{
    return paused;
}

void CommandCenter::setPaused(bool value)
{
    paused = value;
}

bool CommandCenter::getMuted() const
{
    return muted;
}


void CommandCenter::setMuted(bool value)
{
    muted = value;
}

long CommandCenter::getFrame() const
{
    return frame;
}

void CommandCenter::setFrame(long frame_in)
{
    frame = frame_in;
}

QVector<Movable*>& CommandCenter::getMovDebris() 
{
    return movDebris;
}

void CommandCenter::setMovDebris( QVector<Movable*>& value)
{
    movDebris = value;
}

QVector<Movable*>& CommandCenter::getMovFriends() 
{
    return movFriends;
}

void CommandCenter::setMovFriends( QVector<Movable*>& value)
{
    movFriends = value;
}

QVector<Movable*>& CommandCenter::getMovFoes() 
{
    return movFoes;
}

void CommandCenter::setMovFoes(QVector<Movable*>& value)
{
    movFoes.clear();
    movFoes = value;
}

QVector<Movable*> &CommandCenter::getMovFloaters() 
{
    return movFloaters;
}

void CommandCenter::setMovFloaters( QVector<Movable*>& value)
{
    movFloaters = value;
}

GameOpsQueue* CommandCenter::getOpsQueue() 
{
    return opsQueue;
}

void CommandCenter::setOpsQueue(GameOpsQueue* value)
{
    opsQueue = value;
}

Falcon* CommandCenter::getFalcon() const {
    return falcon;
}

Star* CommandCenter::getStar() const {
    Star* star = nullptr;
    for(int i = 0 ; i < movDebris.length(); i++)
    {
        Movable* m = movDebris.at(i);
        if((star = dynamic_cast<Star*>(m)))
            return star;
    }
    return star;
}


CommandCenter::CommandCenter()
{
    //falcon = nullptr;
    falcon = new Falcon();
    opsQueue = new GameOpsQueue();
}

CommandCenter::~CommandCenter()
{
    if (falcon) {
        delete falcon;
        falcon = nullptr;
    }
    if (opsQueue) {
        delete opsQueue;
        opsQueue = nullptr;
    }
}

void CommandCenter::clearAll()  {
    //qDeleteAll(movDebris);
    movDebris.clear();

   // qDeleteAll(movFriends);
	movFriends.clear();
	
    //(movFoes);
    movFoes.clear();
	
    //qDeleteAll(movFloaters);
    movFloaters.clear();
}

void CommandCenter::generateStarField()
{
    int count = 100;
	while (count-- > 0){
        Star* w_star = new Star();
        addOp(GameOp(w_star, GameOp::ADD));
	}
}


bool CommandCenter::isGameOver()  {
    return numFalcons < 1;
}
