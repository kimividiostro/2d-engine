#pragma once

#include "State.h"

class MovingState : public State {
	bool m_movingRight;
public:
	MovingState(bool movingRight);
	void enter(std::shared_ptr<Entity>& owner) override;
	std::shared_ptr<State> handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands) override;
	std::shared_ptr<State> update(std::shared_ptr<Entity>& owner, float deltaTime) override;
	void exit(std::shared_ptr<Entity>&) override;
};