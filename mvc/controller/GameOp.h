#ifndef GAMEOP_H
#define GAMEOP_H


#include "Movable.h"

class GameOp {
public:
    enum class Action {
        ADD, REMOVE
    };

    // Constructor
    GameOp(Movable* movable, Action action);

    // Getters
    Movable* getMovable() const;
    Action getAction() const;

private:
    Movable* m_movable;
    Action m_action;
};

/**
#include "Movable.h"

class GameOp
{
public:
    enum Action {
        ADD, REMOVE
    };

    // Constructor
    GameOp(Movable *movable, Action action);

    // Getters
    Movable* getMovable();
    Action getAction();

private:
    Movable *m_movable;
    Action m_action;
};
**/

#endif // GAMEOP_H
