#pragma once
#include"State.h"

class IdleState : public State {
public:
    IdleState() = default;
    void enter(Entity& owner) override;
    State* handleInput(Entity& owner, InputManager& inputManager) override;
    State* update(Entity& owner, float deltaTime) override;
    void exit(Entity& owner) override;

};