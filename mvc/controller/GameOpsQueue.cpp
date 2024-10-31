
#include "GameOpsQueue.h"

void GameOpsQueue::enqueue(std::shared_ptr<Movable> mov, GameOp::Action action)
{
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(GameOp(mov, action));
}

GameOp GameOpsQueue::dequeue()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (queue.empty()) {
        throw std::runtime_error("Attempted to dequeue from an empty queue.");
    }
    GameOp gameOp = queue.front();
    queue.pop();
    return gameOp;
}

bool GameOpsQueue::isEmpty() const
{
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}
