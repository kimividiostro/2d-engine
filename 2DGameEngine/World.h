#pragma once
#include"EntityManager.h"
#include"GameplayCollisionSystem.h"
#include"MovementSystem.h"

class World {
public:
	World();
	EntityManager m_entityManager;
	GameplayCollisionSystem m_collisionSystem;
	MovementSystem m_movementSystem;
};