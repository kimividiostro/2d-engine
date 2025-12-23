#include "MovingState.h"
#include"IdleState.h"
#include "JumpingState.h"
#include "FallingState.h"


MovingState::MovingState(short direction) : m_direction(direction) {}

void MovingState::enter(Entity& owner) {
	std::cout << "Entered MovingState" << std::endl;
	owner.movement->direction = m_direction;
}

State* MovingState::handleInput(Entity& owner, std::vector<Command>& commands, std::map<int, bool>& inputState) {
	for (auto& command : commands) {
		if (command.m_type == START) {
			switch (command.m_name) {
			case JUMP:
				return new JumpingState();
			default:
				break;
			}
		}
		if (command.m_type == END) {
			switch (command.m_name) {
			case MOVE_LEFT:
				if (m_direction == -1) {
					owner.movement->direction = 0;
					return new IdleState();
				}
				break;
			case MOVE_RIGHT:
				if (m_direction == 1) {
					owner.movement->direction = 0;
					return new IdleState(); 
				}
				break;
			default:
				break;
			}
		}
	}
	return nullptr;
}

State* MovingState::update(Entity& owner, float deltaTime) {
	if (owner.movement->jumpRequested) {
		return new JumpingState();
	}

	if (!owner.movement->isOnGround) {
		return new FallingState();
	}

	return nullptr;
}

void MovingState::exit(Entity& owner) {
	std::cout << "Exited MovingState" << std::endl;
}