#include "JumpSystem.h"
#include"World.h"

void JumpSystem::update(float deltaTime)
{
	auto entities = m_world.view<Movement, JumpRequest, JumpComponent>();
	for (auto& e : entities) {
		auto& movement = m_world.get<Movement>(e);
		auto& jump = m_world.get<JumpComponent>(e);
		movement.velocity.y = jump.jumpVelocity;
		m_world.remove<JumpRequest>(e);
	}
}
