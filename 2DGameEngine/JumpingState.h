#pragma once
#include "State.h"

class JumpingState : public State {
public:
	JumpingState() = default;
	void enter(Entity& owner) override;
	State* handleInput(Entity&, InputManager& inputManager) override;
	State* update(Entity&, float deltaTime) override;
	void exit(Entity& owner) override;
};