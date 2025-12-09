#include "MovingState.h"
#include"IdleState.h"
#include "JumpingState.h"
#include "FallingState.h"


MovingState::MovingState(short direction) : m_direction(direction) {}

void MovingState::enter(std::shared_ptr<Entity>& owner) {
	owner->movement->direction = m_direction;
}

std::shared_ptr<State> MovingState::handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands) {
	for (auto& command : commands) {
		if (command.m_type == START) {
			switch (command.m_name) {
			case JUMP:
				return std::make_shared<JumpingState>(true);
			/*case MOVE_LEFT:
				if (m_direction == -1) {
					break;
				}
				m_direction = -1;
				owner->movement->direction = m_direction;
				break;
			case MOVE_RIGHT:
				if (m_direction == 1) {
					break;
				}
				m_direction = 1;
				owner->movement->direction = m_direction;
				break;*/
			default:
				break;
			}
		}
		if (command.m_type == END) {
			switch (command.m_name) {
			case MOVE_LEFT:
				if (m_direction == -1) {
					return std::make_shared<IdleState>();
				}
				break;
			case MOVE_RIGHT:
				if (m_direction == 1) { 
					return std::make_shared<IdleState>(); 
				}
				break;
			default:
				break;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<State> MovingState::update(std::shared_ptr<Entity>& owner, float deltaTime) {
	if (!owner->movement->isOnGround) {
		return std::make_shared<FallingState>();
	}
	std::cout << "Moving... On ground: " << owner->movement->isOnGround;

	return nullptr;
}

void MovingState::exit(std::shared_ptr<Entity>& owner) {
	owner->movement->direction = 0;
}