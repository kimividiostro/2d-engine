#pragma once
#include "State.h"

class JumpingState : public State {
private:
	float m_jumpForce = 1000.f;
	bool m_moving = false;
public:
	JumpingState(bool moving);
	void enter(Entity& owner) override;
	State* handleInput(Entity&, std::vector<Command>& commands) override;
	State* update(Entity&, float deltaTime) override;
	void exit(Entity& owner) override;
};