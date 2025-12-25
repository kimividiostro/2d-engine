#include "FallingState.h"
#include "IdleState.h"
#include "MovingState.h"

void FallingState::enter(Entity& owner) {
	std::cout << "Entered FallingState" << std::endl;
}

State* FallingState::handleInput(Entity& owner, InputManager& inputManager) {
    for (auto& command : inputManager.getCommandsSinceLastFrame()) {
        if (command.m_type == START) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                owner.movement->direction = -1;
                break;
            case MOVE_RIGHT:
                owner.movement->direction = 1;
                break;
            case JUMP:
                owner.movement->jumpRequested = true;
                break;
            default:
                break;
            }
        }
        if (command.m_type == END) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                if (owner.movement->direction == -1) {
                    owner.movement->direction = 0;
                }
                break;
            case MOVE_RIGHT:
                if (owner.movement->direction == 1) {
                    owner.movement->direction = 0;
                }
                break;
            default:
                break;
            }
        }
    }
    return nullptr;
}

State* FallingState::update(Entity& owner, float deltaTime) {
	if (owner.movement->isOnGround) {
        if (owner.movement->direction == 0) {
		    return new IdleState();
        }
        return new MovingState(owner.movement->direction);
	}
	return nullptr;
}

void FallingState::exit(Entity& owner) {
	std::cout << "Exited FallingState" << std::endl;
}