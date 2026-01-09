#pragma once
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include "InputState.h"
#include "Command.h"
#include "InputManager.h"
#include "World.h"
#include "GameplayCollisionSystem.h"

class Game {
	World m_world;
	sf::RenderWindow m_window;
	InputManager m_inputManager;

	int m_screenWidth = 800;
	int m_screenHeight = 600;
	int m_fps = 60;

	void processInput();
	void render();
	void spawnEnemy();
	void createMap();

	public:

	Game();
	void run();
};