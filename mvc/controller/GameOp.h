#ifndef GAMEOP_H
#define GAMEOP_H

#include "Movable.h"
#include <memory>

class GameOp {
public:
    // Define the Action enumeration
    enum class Action {
        ADD, REMOVE
    };

private:
    std::shared_ptr<Movable> movable;  // Pointer to a Movable object
    Action action;                     // Action to be performed (ADD or REMOVE)

public:
    // Constructor
    GameOp(std::shared_ptr<Movable> movableObj, Action act)
        : movable(movableObj), action(act) {}

    // Getters and Setters
    std::shared_ptr<Movable>& getMovable() { return movable; }
    void setMovable(std::shared_ptr<Movable> movableObj) { movable = movableObj; }

    Action& getAction() { return action; }
    void setAction(Action act) { action = act; }
};

#endif
