#include "JumpingState.h"
#include "IdleState.h"

JumpingState::JumpingState(bool moving) : m_moving(moving) {}

void JumpingState::enter(std::shared_ptr<Entity>& owner) 
{
    if (m_moving) {
        owner->transform->velocity.x = owner->transform->previousPosition < owner->transform->position ? 150.f : -150.f;
    }
    std::cout << "Entered JumpingState...";
}

std::shared_ptr<State> JumpingState::handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands)
{
    for (auto& command : commands) {
        if (command.m_type == START) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                owner->transform->velocity.x = -150;
                break;
            case MOVE_RIGHT:
                owner->transform->velocity.x = 150;
                break;
            default:
                break;
            }
        }
        if (command.m_type == END) {
            switch (command.m_name)
            {
            case MOVE_LEFT:
                owner->transform->velocity.x = 0;
                break;
            case MOVE_RIGHT:
                owner->transform->velocity.x = 0;
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
    std::cout << "Force: " << m_jumpForce;
    owner->transform->previousPosition = owner->transform->position;
    owner->transform->position.y -= m_jumpForce * deltaTime;
    owner->transform->position.x += owner->transform->velocity.x * deltaTime;
    if (m_jumpForce > 0) {
        m_jumpForce -= 200.f * deltaTime;
        return nullptr;
    }
    return std::make_shared<IdleState>();
}

void JumpingState::exit(std::shared_ptr<Entity>& owner)
{
    std::cout << "Exited JumpingState...";
}
