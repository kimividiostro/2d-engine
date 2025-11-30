#include "IdleState.h"
#include "MovingState.h"

void IdleState::enter(std::shared_ptr<Entity>& owner) {
	std::cout << "Entered idle state...";
	owner->transform->velocity = { 0,0 };
}

std::shared_ptr<State> IdleState::handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands) {
	for(const Command& command : commands)
	{
		if (command.m_type == START) {
			switch (command.m_name) {
			case MOVE_LEFT:
				return std::make_shared<MovingState>(false);
			case MOVE_RIGHT:
				return std::make_shared<MovingState>(true);
			default:
				break;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<State> IdleState::update(std::shared_ptr<Entity>& owner, float deltaTime) {
	std::cout << "Idling....";
	return nullptr;
}

void IdleState::exit(std::shared_ptr<Entity>& owner) {
	std::cout << "Exited idle state...";
}