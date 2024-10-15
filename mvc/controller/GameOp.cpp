#include "GameOp.h"

// Constructor implementation
GameOp::GameOp(Movable* movable, Action action)
    : m_movable(movable), m_action(action) {}

// Getter implementations
Movable* GameOp::getMovable() const {
    return m_movable;
}

GameOp::Action GameOp::getAction() const {
    return m_action;
}


/**
#include "GameOp.h"

// Constructor implementation
GameOp::GameOp(Movable *movable, Action action)
{
    m_movable = movable;
    m_action = action;
}

// Getter implementations
Movable* GameOp::getMovable()
{
    return m_movable;
}

GameOp::Action GameOp::getAction()
{
    return m_action;
}
**/
