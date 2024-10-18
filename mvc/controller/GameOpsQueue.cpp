
#include "GameOpsQueue.h"

void GameOpsQueue::enqueue(const GameOp &op) {
    gameOps.push_back(op);
}

GameOp GameOpsQueue::dequeue() {
    if (!gameOps.empty()) {
        GameOp op = gameOps.front();
        gameOps.erase(gameOps.begin());
        return op;
    }
    return GameOp("NONE");
}

bool GameOpsQueue::isEmpty() const {
    return gameOps.empty();
}
