#include "IdleState.h"
#include "MovingState.h"
#include "JumpingState.h"

void IdleState::enter(Entity& owner) {
	std::cout << "Entered IdleState..." << std::endl;
}

State* IdleState::handleInput(Entity& owner, InputManager& inputManager) {
 	for(const Command& command : inputManager.getCommandsSinceLastFrame())
	{
		if (command.m_type == START) {
			switch (command.m_name) {
			case MOVE_LEFT:
				return new MovingState(-1);
			case MOVE_RIGHT:
				return new MovingState(1);
			case JUMP:
				return new JumpingState();
			default:
				break;
			}
		}
	}
	return nullptr;
}

State* IdleState::update(Entity& owner, float deltaTime) {
	if (owner.movement->jumpRequested) {
		return new JumpingState();
	}
	return nullptr;
}

void IdleState::exit(Entity& owner) {
	std::cout << "Exited IdleState..." << std::endl;
}