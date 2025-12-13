#include "IdleState.h"
#include "MovingState.h"
#include "JumpingState.h"

void IdleState::enter(Entity& owner) {
	std::cout << "Entered idle state...";
	owner.movement->velocity = { 0,0 };
}

State* IdleState::handleInput(Entity& owner, std::vector<Command>& commands) {
 	for(const Command& command : commands)
	{
		if (command.m_type == START) {
			switch (command.m_name) {
			case MOVE_LEFT:
				return new MovingState(-1);
			case MOVE_RIGHT:
				return new MovingState(1);
			case JUMP:
				return new JumpingState(false);
			default:
				break;
			}
		}
	}
	return nullptr;
}

State* IdleState::update(Entity& owner, float deltaTime) {
	std::cout << "Idling....";
	return nullptr;
}

void IdleState::exit(Entity& owner) {
	std::cout << "Exited idle state...";
}