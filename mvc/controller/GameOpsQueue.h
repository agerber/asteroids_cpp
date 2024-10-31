#ifndef GAMEOPSQUEUE_H
#define GAMEOPSQUEUE_H

#include <queue>
#include <mutex>
#include <memory>
#include "GameOp.h"

// Effectively a Queue that enqueues and dequeues Game Operations (add/remove)
class GameOpsQueue {
public:
    GameOpsQueue() = default;

    // Method to enqueue a GameOp with a movable object and an action
    void enqueue(std::shared_ptr<Movable> mov, GameOp::Action action) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(GameOp(mov, action));
    }

    // Method to dequeue a GameOp
    GameOp dequeue() {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) {
            throw std::runtime_error("Attempted to dequeue from an empty queue.");
        }
        GameOp gameOp = queue.front();
        queue.pop();
        return gameOp;
    }

    // Check if the queue is empty
    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

private:
    std::queue<GameOp> queue;  // Queue to hold GameOp objects
    mutable std::mutex mutex;  // Mutex for thread safety
};

#endif // GAMEOPSQUEUE_H
