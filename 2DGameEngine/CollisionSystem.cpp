#include "CollisionSystem.h"

bool CollisionSystem::InBoundsOfWindow(const int screenWidth, const int screenHeight, const std::shared_ptr<Entity>& entity) {
	return (
		entity->transform->position.x - entity->boundingBox->halfWidth >= 0
		&& entity->transform->position.x + entity->boundingBox->halfWidth <= screenWidth
		&& entity->transform->position.y - entity->boundingBox->halfHeight >= 0
		&& entity->transform->position.y + entity->boundingBox->halfHeight <= screenHeight);
}

CollisionInfo CollisionSystem::CheckEntityCollision(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2) {
	int dx = abs(e1->transform->position.x - e2->transform->position.x);
	int dy = abs(e1->transform->position.y - e2->transform->position.y);
	
	int ox = e1->boundingBox->halfWidth + e2->boundingBox->halfWidth - dx;
	int oy = e1->boundingBox->halfHeight + e2->boundingBox->halfHeight - dy;
	
	return { ox > 0 && oy > 0, Vec2(ox, oy) };
}

void CollisionSystem::ResolveCollision(std::shared_ptr<Entity> entity, CollisionInfo collisionInfo) {
	float x = 0;
	if (entity->transform->position.x > entity->transform->previousPosition.x) {
		x = collisionInfo.overlap.x * -1;
	}
	else if (entity->transform->position.x < entity->transform->previousPosition.x) {
		x = collisionInfo.overlap.x;
	}
	float y = 0;
	if (entity->transform->position.y > entity->transform->previousPosition.y) {
		y = collisionInfo.overlap.y * -1;
	}
	else if (entity->transform->position.y < entity->transform->previousPosition.y) {
		y = collisionInfo.overlap.y;
	}
	Vec2 resolve = { x, y };
	entity->transform->position += resolve;
}

Vec2 CollisionSystem::GetPreviousOverlap(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2) {
	int dx = abs(e1->transform->previousPosition.x - e2->transform->position.x);
	int dy = abs(e1->transform->previousPosition.y - e2->transform->position.y);

	int ox = e1->boundingBox->halfWidth + e2->boundingBox->halfWidth - dx;
	int oy = e1->boundingBox->halfHeight + e2->boundingBox->halfHeight - dy;

	return Vec2(ox, oy);
}

void CollisionSystem::ResetEntityPositionInsideWindow(const int screenWidth, const int screenHeight, std::shared_ptr<Entity>& entity) {
	if (entity->transform->position.x > screenWidth) {
		entity->transform->position.x = screenWidth - entity->boundingBox->halfWidth - 1;
	}
	if (entity->transform->position.x < 0) {
		entity->transform->position.x = entity->boundingBox->halfWidth + 1;
	}
	if (entity->transform->position.y > screenHeight) {
		entity->transform->position.y = screenHeight - entity->boundingBox->halfHeight - 1;
	}
	if (entity->transform->position.y < 0) {
		entity->transform->position.y = entity->boundingBox->halfHeight + 1;
	}
}