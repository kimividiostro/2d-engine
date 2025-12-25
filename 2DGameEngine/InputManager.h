#pragma once

#include "InputState.h"
#include "Command.h"
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

class InputManager
{
	std::map<int, CommandName> m_inputMap;
	std::map<int, bool> m_inputState;
	std::vector<Command> m_commands;
public:
	void registerCommand(const sf::Keyboard::Key& key, const CommandName& commandName);
	void addCommand(CommandType type, CommandName name);

	CommandName getCommandNameByKey(const sf::Keyboard::Key& key);

	void setCommandState(const CommandName& command, bool isActive);
	bool getCommandState(const CommandName& command);

	std::vector<Command>& getCommandsSinceLastFrame();
	void clearCommands();
};

