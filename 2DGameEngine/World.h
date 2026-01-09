#pragma once
#include"EntityManager.h"
#include"GameplayCollisionSystem.h"

class World {
public:
	World();
	EntityManager m_entityManager;
	GameplayCollisionSystem m_collisionSystem;
};