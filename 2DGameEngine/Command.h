#pragma once

enum CommandType {
	START,
	END
};

enum CommandName {
	MOVE_LEFT = 1,
	MOVE_RIGHT,
	JUMP,
	SHOOT
};

struct Command
{
	CommandType m_type;
	CommandName m_name;

	Command(CommandType type, CommandName name) : m_type(type), m_name(name) {}
};

