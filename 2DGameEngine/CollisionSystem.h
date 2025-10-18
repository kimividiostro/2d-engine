#pragma once
#include "Vec2.h"
#include "Entity.h"

struct CollisionInfo {
	bool collided = false;
	Vec2 overlap = { 0,0 };
};

static class CollisionSystem {
public:
	static bool InBoundsOfWindow(const int screenWidth, const int screenHeight, const std::shared_ptr<Entity>& entity);
	static CollisionInfo CheckEntityCollision(const std::shared_ptr<Entity>& entity1, const std::shared_ptr<Entity>& entity2);
	static void ResetEntityPositionInsideWindow(const int screenWidth, const int screenHeight, std::shared_ptr<Entity>& entity);
};