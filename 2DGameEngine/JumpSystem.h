#pragma once
#include"System.h"

class World;

class JumpSystem : public System
{
	World& m_world;
public:
	explicit JumpSystem(World& world)
		: m_world(world) {
	}

	void update(float deltaTime) override;
};

