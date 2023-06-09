#include "GameOpsQueue.h"

GameOpsQueue::GameOpsQueue()
{
    lock = new QMutex();
}

void GameOpsQueue::enqueue(Movable* mov, GameOp::Action action)
{
    lock->lock();
    push_back(new GameOp(mov, action));
    lock->unlock();
}

void GameOpsQueue::enqueue(GameOp op)
{
    enqueue(op.getMovable(), op.getAction());
}

GameOp* GameOpsQueue::dequeue()
{
    lock->lock();
    GameOp* gameOp = first();
    removeFirst();
    lock->unlock();
    return gameOp;
}

bool GameOpsQueue::isExist(Movable* mov)
{
    lock->lock();
    for (int j = 0; j < size(); j++)
    {
        Movable* other = at(j)->getMovable();
        GameOp::Action action2 = at(j)->getAction();

        if (other == mov && action2 == GameOp::Action::REMOVE)
        {
            lock->unlock();
            return true;
        }
    }
    lock->unlock();
    return false;
}
