#pragma once
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include "InputState.h"
#include "Command.h"
#include "InputManager.h"
#include "World.h"
#include "GameplayCollisionSystem.h"
#include"RenderingSystem.h"

class Game {
	World m_world;
	sf::RenderWindow m_window;
	InputManager m_inputManager;

	RenderingSystem m_renderingSystem = RenderingSystem(&m_world, &m_window);

	int m_screenWidth = 800;
	int m_screenHeight = 600;
	int m_fps = 60;

	void processInput();
	void spawnEnemy();
	void createMap();

	public:

	Game();
	void run();
};