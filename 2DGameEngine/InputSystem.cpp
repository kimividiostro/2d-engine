#include "InputSystem.h"
#include<iostream>

void InputSystem::update(float deltaTime)
{
	sf::Event event;

	m_inputManager.clearCommands();
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();

		auto commandName = m_inputManager.getCommandNameByKey(event.key.code);
		if (commandName == 0) {
			continue;
		}

		if (event.type == sf::Event::KeyPressed) {
			m_inputManager.addCommand(START, commandName);
			m_inputManager.setCommandState(commandName, true);
			std::cout << "START " << commandName << std::endl;
		}

		if (event.type == sf::Event::KeyReleased) {
			m_inputManager.addCommand(END, commandName);
			m_inputManager.setCommandState(commandName, false);
			std::cout << "END " << commandName << std::endl;
		}
	}
}
