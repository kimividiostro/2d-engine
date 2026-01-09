#include "CollisionSystem.h"
#include "GameplayCollisionSystem.h"
#include "World.h"

void GameplayCollisionSystem::update(float deltaTime)
{
	auto& entityManager = m_world.m_entityManager;
	for (auto entity : m_world.m_entityManager.GetAllEntities()) {
		if (!entity->transform) {
			continue;
		}
		if (entity->getType() != PLAYER) {
			auto player = entityManager.GetEntitiesByType(PLAYER)[0];
			auto collisionInfo = CollisionSystem::CheckEntityCollision(*player, *entity);
			if (collisionInfo.collided) {
				CollisionSystem::ResolveCollision(*player, collisionInfo);
				if (entity->getType() == FLOOR || (entity->getType() == WALL && collisionInfo.axis == Y_AXIS && entity->transform->position.y > player->transform->position.y)) {
					player->movement->velocity.y = 0;
					player->movement->isOnGround = true;
				}
			}
			else if (entity->getType() == FLOOR) {
				player->movement->isOnGround = false;
			}
		}
	}
}
