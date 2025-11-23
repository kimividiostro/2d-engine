#include"Engine.h"

void Engine::run() {

}

void Engine::update() {

}

void Engine::createWindow(int width, int height, std::string title) {
	m_window.create(sf::VideoMode(width, height), title);
}

