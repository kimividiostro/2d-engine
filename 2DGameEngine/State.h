#pragma once
#include <vector>
#include "Command.h"
#include <memory>
#include"iostream"
#include "Entity.h"

class State
{
public:
	virtual ~State() = default;
	virtual void enter(Entity& owner) = 0;
	virtual State* handleInput(Entity&, std::vector<Command>& commands, std::map<int, bool>& inputState) = 0;
	virtual State* update(Entity&, float deltaTime) = 0;
	virtual void exit(Entity& owner) = 0;
};

