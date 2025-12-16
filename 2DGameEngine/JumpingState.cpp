#include "JumpingState.h"
#include "IdleState.h"
#include "FallingState.h"

void JumpingState::enter(Entity& owner) 
{
    std::cout << "Entered JumpingState..." << std::endl;
    owner.movement->velocity.y = owner.movement->jumpVelocity;
    owner.movement->isOnGround = false;
}

State* JumpingState::handleInput(Entity& owner, std::vector<Command>& commands)
{
    for (auto& command : commands) {
        if (command.m_type == START) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                owner.movement->direction = -1;
                break;
            case MOVE_RIGHT:
                owner.movement->direction = 1;
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
            case JUMP:
                owner.movement->velocity.y *= 0.4f;
                break;
            default:
                break;
            }
        }
    }
    return nullptr;
}

State* JumpingState::update(Entity& owner, float deltaTime)
{
    if (owner.movement->isOnGround) {
        return new IdleState();
    }

    if (owner.movement->velocity.y > 0) {
        return new FallingState();
    }

    return nullptr;
}

void JumpingState::exit(Entity& owner)
{
    std::cout << "Exited JumpingState..." << std::endl;
}
