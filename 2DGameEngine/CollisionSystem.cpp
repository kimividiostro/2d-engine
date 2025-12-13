#include "CollisionSystem.h"

bool CollisionSystem::InBoundsOfWindow(const int screenWidth, const int screenHeight, const Entity& entity) {
	return (
		entity.transform->position.x - entity.boundingBox->halfWidth >= 0
		&& entity.transform->position.x + entity.boundingBox->halfWidth <= screenWidth
		&& entity.transform->position.y - entity.boundingBox->halfHeight >= 0
		&& entity.transform->position.y + entity.boundingBox->halfHeight <= screenHeight);
}

CollisionInfo CollisionSystem::CheckEntityCollision(const Entity& e1, const Entity& e2) {
	CollisionInfo info;
	
	float dx = e1.transform->position.x - e2.transform->position.x;
	float dy = e1.transform->position.y - e2.transform->position.y;

	float ox = e1.boundingBox->halfWidth + e2.boundingBox->halfWidth - std::fabs(dx);
	float oy = e1.boundingBox->halfHeight + e2.boundingBox->halfHeight - std::fabs(dy);

	if (ox > 0 && oy > 0) {
		info.collided = true;
		info.overlap = { ox, oy };
		info.axis = ox < oy ? X_AXIS: Y_AXIS;
		info.normal = {
			(dx > 0 ? 1.f : -1.f),
			(dy > 0 ? 1.f : -1.f)
		};
	}
	
	return info;
}

void CollisionSystem::ResolveCollision(Entity& entity, CollisionInfo collisionInfo) {
	if (collisionInfo.axis == X_AXIS)
	{
		entity.transform->position.x += collisionInfo.overlap.x * collisionInfo.normal.x;
		entity.movement->velocity.x = 0;
	}
	else if (collisionInfo.axis == Y_AXIS)
	{
		entity.transform->position.y += collisionInfo.overlap.y * collisionInfo.normal.y;
		entity.movement->velocity.y = 0;
	}
}

Vec2 CollisionSystem::GetPreviousOverlap(const Entity& e1, const Entity& e2) {
	int dx = abs(e1.transform->previousPosition.x - e2.transform->position.x);
	int dy = abs(e1.transform->previousPosition.y - e2.transform->position.y);

	int ox = e1.boundingBox->halfWidth + e2.boundingBox->halfWidth - dx;
	int oy = e1.boundingBox->halfHeight + e2.boundingBox->halfHeight - dy;

	return Vec2(ox, oy);
}

void CollisionSystem::ResetEntityPositionInsideWindow(const int screenWidth, const int screenHeight, Entity& entity) {
	if (entity.transform->position.x > screenWidth) {
		entity.transform->position.x = screenWidth - entity.boundingBox->halfWidth - 1;
	}
	if (entity.transform->position.x < 0) {
		entity.transform->position.x = entity.boundingBox->halfWidth + 1;
	}
	if (entity.transform->position.y > screenHeight) {
		entity.transform->position.y = screenHeight - entity.boundingBox->halfHeight - 1;
	}
	if (entity.transform->position.y < 0) {
		entity.transform->position.y = entity.boundingBox->halfHeight + 1;
	}
}