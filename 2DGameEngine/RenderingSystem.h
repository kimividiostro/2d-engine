#pragma once
#include"System.h"

class World;

class RenderingSystem : public System {
	World* m_world;
	sf::RenderWindow* m_window;
public:
	RenderingSystem(World* world, sf::RenderWindow* window) : m_world(world), m_window(window) {}
	void update(float deltaTime) override;
};