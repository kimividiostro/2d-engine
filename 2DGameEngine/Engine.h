#pragma once
#include"EntityManager.h"
#include"Scene.h"

class Engine {
	sf::RenderWindow m_window;
	EntityManager m_entityManager;
	std::map<std::string, std::shared_ptr<Scene>> m_scenes;

	void run();
	void update();
	std::shared_ptr<Scene> changeScene(std::string scene);
	void createWindow(int width, int height, std::string title);
};