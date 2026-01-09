#pragma once
#include "System.h"

class World;

class GameplayCollisionSystem : public System {
	World& m_world;
public:
	explicit GameplayCollisionSystem(World& world)
		: m_world(world) {}

	void update(float deltaTime) override;
};