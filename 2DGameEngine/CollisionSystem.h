#pragma once
#include "Vec2.h"
#include "Entity.h"

enum Axis {
	X_AXIS,
	Y_AXIS,
	NONE
};

struct CollisionInfo {
	bool collided = false;
	Vec2 overlap = { 0,0 };
	Axis axis = NONE;
	Vec2 normal = { 0,0 };
};

static class CollisionSystem {
public:
	static bool InBoundsOfWindow(const int screenWidth, const int screenHeight, const Entity& entity);
	static CollisionInfo CheckEntityCollision(const Entity& entity1, const Entity& entity2);
	static Vec2 GetPreviousOverlap(const Entity& entity1, const Entity& entity2);
	static void ResetEntityPositionInsideWindow(const int screenWidth, const int screenHeight, Entity& entity);
	static void ResolveCollision(Entity& entity1, CollisionInfo collisionInfo);
};