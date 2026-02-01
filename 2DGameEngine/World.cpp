#include "World.h"

World::World() : 
	m_entityManager(), 
	m_collisionSystem(*this), 
	m_movementSystem(*this), 
	m_jumpSystem(*this) {

}