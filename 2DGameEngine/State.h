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
	virtual void enter(std::shared_ptr<Entity>& owner) = 0;
	virtual std::shared_ptr<State> handleInput(std::shared_ptr<Entity>&, std::vector<Command>& commands) = 0;
	virtual std::shared_ptr<State> update(std::shared_ptr<Entity>&, float deltaTime) = 0;
	virtual void exit(std::shared_ptr<Entity>& owner) = 0;
};

