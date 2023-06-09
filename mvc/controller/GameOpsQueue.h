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