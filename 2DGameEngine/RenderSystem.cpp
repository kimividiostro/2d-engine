#include"RenderSystem.h"
#include"World.h"

void RenderSystem::update() {
	auto entities = m_world.view<Transform, ShapeRender>();

	for (auto& entity : entities) {
		auto transform = m_world.get<Transform>(entity);
		auto render = m_world.get<ShapeRender>(entity);
		render.shape.setPosition(transform.position.x, transform.position.y);
		m_renderWindow->draw(render.shape);
	}
}