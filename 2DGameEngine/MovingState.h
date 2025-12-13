#pragma once

#include "State.h"

class MovingState : public State {
	short m_direction = 0;

public:
	MovingState(short direction);
	void enter(Entity& owner) override;
	State* handleInput(Entity& owner, std::vector<Command>& commands) override;
	State* update(Entity& owner, float deltaTime) override;
	void exit(Entity&) override;
};