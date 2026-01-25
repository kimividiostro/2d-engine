#pragma once
#include"InputManager.h"

class World;

class InputSystem {
	World& m_world;
public:
	InputSystem(World& world) : m_world(world) {}
	void update();
};