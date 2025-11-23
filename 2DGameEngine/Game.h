#pragma once
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include "InputState.h"

class Game {
	EntityManager m_entityManager;
	sf::RenderWindow m_window;
	InputState m_inputState;

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