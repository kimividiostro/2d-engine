#pragma once
#include"SFML/Graphics/RenderWindow.hpp"

class World;

class RenderSystem {
public:
	sf::RenderWindow* m_renderWindow = nullptr;
	World& m_world;

	RenderSystem(sf::RenderWindow& window, World& world) : m_world(world) {};

	void update();
};