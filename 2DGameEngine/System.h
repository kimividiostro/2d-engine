#pragma once
#include <vector>
#include "Entity.h"

class System {
public:
	virtual ~System() = default;
	virtual void update(float deltaTime) = 0;
};