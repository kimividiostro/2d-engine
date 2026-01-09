#include "MovementSystem.h"
#include "World.h"

void MovementSystem::update(float deltaTime)
{
	for (auto entity : m_world.m_entityManager.GetAllEntities()) {
		if (!entity->movement) {
			return;
		}
		auto moveCom = entity->movement;
		entity->transform->previousPosition = entity->transform->position;
		if (moveCom->direction != 0) {
			moveCom->velocity.x += moveCom->acceleration * moveCom->direction;
			if (fabs(moveCom->velocity.x) > moveCom->maxSpeed) {
				moveCom->velocity.x = moveCom->maxSpeed * moveCom->direction;
			}
		}
		else {
			if (moveCom->velocity.x > 0) {
				moveCom->velocity.x -= moveCom->friction * deltaTime;
				if (moveCom->velocity.x < 0) {
					moveCom->velocity.x = 0;
				}
			}
			if (moveCom->velocity.x < 0) {
				moveCom->velocity.x += moveCom->friction * deltaTime;
				if (moveCom->velocity.x > 0) {
					moveCom->velocity.x = 0;
				}
			}
		}

		if (!moveCom->isOnGround) {
			moveCom->velocity.y += moveCom->gravity * deltaTime;
		}

		if (moveCom->jumpRequested) {
			moveCom->jumpBufferTimer += deltaTime;
			if (moveCom->jumpBufferTimer > moveCom->jumpBufferTime) {
				moveCom->jumpRequested = false;
				moveCom->jumpBufferTimer = 0;
			}
		}

		entity->movement->velocity.y += entity->movement->gravity * deltaTime;
		entity->transform->position += entity->movement->velocity * deltaTime;
	}
}
