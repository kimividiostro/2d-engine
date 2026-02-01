#include "RenderingSystem.h"
#include"World.h"

void RenderingSystem::update(float deltaTime)
{
	m_window->clear();
	auto entities = m_world->view<Transform, Render>();
	for (auto e : entities) {
		auto& transform = m_world->get<Transform>(e);
		auto& render = m_world->get<Render>(e);
		render.sfShape.setPosition(transform.position.x, transform.position.y); // Move this into a system
		m_window->draw(render.sfShape);
	}

	m_window->display();
}
