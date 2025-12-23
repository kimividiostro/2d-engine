#pragma once
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include "InputState.h"
#include "Command.h"

class Game {
	EntityManager m_entityManager;
	sf::RenderWindow m_window;
	std::map<int, CommandName> m_inputMap;
	std::map<int, bool> m_inputState;
	std::vector<Command> m_commands;

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