#include "GameOpsQueue.h"

GameOpsQueue::GameOpsQueue() = default;

void GameOpsQueue::enqueue(Movable* mov, GameOp::Action action) {
    std::lock_guard<std::mutex> guard(lock);  // Automatically locks and unlocks
    queue.push_back(new GameOp(mov, action));
}

void GameOpsQueue::enqueue(const GameOp& op) {
    enqueue(op.getMovable(), op.getAction());
}

GameOp* GameOpsQueue::dequeue() {
    std::lock_guard<std::mutex> guard(lock);

    if (queue.empty()) {
        return nullptr;
    }

    GameOp* gameOp = queue.front();
    queue.erase(queue.begin());
    return gameOp;
}

bool GameOpsQueue::isExist(Movable* mov) {
    std::lock_guard<std::mutex> guard(lock);

    for (const auto& op : queue) {
        if (op->getMovable() == mov && op->getAction() == GameOp::Action::REMOVE) {
            return true;
        }
    }
    return false;
}

bool GameOpsQueue::empty() const {
    std::lock_guard<std::mutex> guard(lock);
    return queue.empty();
}


/**
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
**/
