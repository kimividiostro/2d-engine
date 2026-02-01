#pragma once
#include"System.h"
#include"InputManager.h"


class InputSystem : public System {
private:
	sf::RenderWindow* m_window;
public:
	InputManager m_inputManager;
	InputSystem(sf::RenderWindow* window) : m_window(window) {}
	void update(float deltaTime) override;
};