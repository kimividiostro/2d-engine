#include "JumpingState.h"
#include "IdleState.h"
#include "FallingState.h"

JumpingState::JumpingState(bool moving) : m_moving(moving) {}

void JumpingState::enter(std::shared_ptr<Entity>& owner) 
{
    owner->movement->velocity.y = owner->movement->jumpVelocity;
    owner->movement->isOnGround = false;
    std::cout << "Entered JumpingState...";
}

std::shared_ptr<State> JumpingState::handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands)
{
    for (auto& command : commands) {
        if (command.m_type == START) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                owner->movement->direction = -1;
                break;
            case MOVE_RIGHT:
                owner->movement->direction = 1;
                break;
            default:
                break;
            }
        }
        if (command.m_type == END) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                if (owner->movement->direction == -1) {
                    owner->movement->direction = 0;
                }
                break;
            case MOVE_RIGHT:
                if (owner->movement->direction == 1) {
                    owner->movement->direction = 0;
                }
                break;
            case JUMP:
                break;
            default:
                break;
            }
        }
    }
    return std::shared_ptr<State>();
}

std::shared_ptr<State> JumpingState::update(std::shared_ptr<Entity>& owner, float deltaTime)
{
    if (owner->movement->isOnGround) {
        return std::make_shared<IdleState>();
    }
    if (owner->movement->velocity.y > 0) {
        return std::make_shared<FallingState>();
    }
    return nullptr;
}

void JumpingState::exit(std::shared_ptr<Entity>& owner)
{
    std::cout << "Exited JumpingState...";
}
