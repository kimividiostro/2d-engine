#pragma once
#include "System.h"

class World;

class MovementSystem : System {
	World& m_world;
public:
	explicit MovementSystem(World& world) : m_world(world) {};
	void update(float deltaTime) override;
};