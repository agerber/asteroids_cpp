#pragma once

#include <vector>
#include <mutex>
#include "GameOp.h"
#include "Movable.h"

class GameOpsQueue {
public:
    GameOpsQueue();

    void enqueue(Movable* mov, GameOp::Action action);
    void enqueue(const GameOp& op);
    GameOp* dequeue();
    bool isExist(Movable* mov);

    bool empty() const;

private:
    std::vector<GameOp*> queue;
    mutable std::mutex lock;  // Use std::mutex for thread safety
};


/**
#pragma once

#include <QVector>
#include <QObject>
#include <QMutex>
#include "GameOp.h"
#include "Movable.h"

class GameOpsQueue : public QVector<GameOp*> {
public:
    GameOpsQueue();
    void enqueue(Movable* mov, GameOp::Action action);
    void enqueue(GameOp op);
    GameOp* dequeue();
    bool isExist(Movable* mov);
private:
    QMutex* lock;
};
**/
