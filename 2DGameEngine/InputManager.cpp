#include "InputManager.h"

void InputManager::registerCommand(const sf::Keyboard::Key& key, const CommandName& commandName) {
	m_inputMap[key] = commandName;
}

void InputManager::addCommand(CommandType type, CommandName name) {
	m_commands.push_back(Command(type, name));
}

CommandName InputManager::getCommandNameByKey(const sf::Keyboard::Key& key) {
	return m_inputMap[key];
}

void InputManager::setCommandState(const CommandName& commandName, bool isActive) {
	m_inputState[commandName] = isActive;
}

bool InputManager::getCommandState(const CommandName& commandName) {
	return m_inputState[commandName];
}

std::vector<Command>& InputManager::getCommandsSinceLastFrame() {
	return m_commands;
}

void InputManager::clearCommands() {
	m_commands.clear();
}