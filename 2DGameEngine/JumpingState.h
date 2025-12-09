#pragma once
#include "State.h"

class JumpingState : public State {
private:
	float m_jumpForce = 1000.f;
	bool m_moving = false;
public:
	JumpingState(bool moving);
	void enter(std::shared_ptr<Entity>& owner) override;
	std::shared_ptr<State> handleInput(std::shared_ptr<Entity>&, std::vector<Command>& commands) override;
	std::shared_ptr<State> update(std::shared_ptr<Entity>&, float deltaTime) override;
	void exit(std::shared_ptr<Entity>& owner) override;
};