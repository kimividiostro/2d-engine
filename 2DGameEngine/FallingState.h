#pragma once
#include "State.h"

class FallingState : public State
{
public:
    FallingState() = default;
    void enter(Entity& owner) override;
    State* handleInput(Entity& owner, std::vector<Command>& commands, std::map<int, bool>& inputState) override;
    State* update(Entity& owner, float deltaTime) override;
    void exit(Entity& owner) override;
};

