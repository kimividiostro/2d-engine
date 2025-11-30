#include "MovingState.h"
#include"IdleState.h"


MovingState::MovingState(bool movingRight) : m_movingRight(movingRight) {}

void MovingState::enter(std::shared_ptr<Entity>& owner) {
	owner->transform->velocity.x = m_movingRight ? 150 : -150;
}

std::shared_ptr<State> MovingState::handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands) {
	for (auto& command : commands) {
		if (command.m_type == END) {
			switch (command.m_name) {
			case MOVE_LEFT:
			case MOVE_RIGHT:
				return std::make_shared<IdleState>();
			defaut:
				break;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<State> MovingState::update(std::shared_ptr<Entity>& owner, float deltaTime) {
	std::cout << "Moving....";
	owner->transform->previousPosition = owner->transform->position;
	owner->transform->position += owner->transform->velocity * deltaTime;
	return nullptr;
}

void MovingState::exit(std::shared_ptr<Entity>& owner) {
	owner->transform->velocity = { 0,0 };
}