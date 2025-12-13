#pragma once
#include <string>
#include "Components.h"

class State;

enum EntityType {
	DEFAULT,
	PLAYER,
	ENEMY,
	PROJECTILE,
	POWERUP,
	FLOOR,
	WALL,
	PLATFORM
};

class Entity {
	friend class EntityManager;

	const int m_id;
	EntityType m_type = DEFAULT;
	bool m_active = true;
	Entity(int id, EntityType type);
	void destroy();
	~Entity();

public:
	bool isActive();
	const EntityType getType();
	const int getId();
	State* state;

	CTransform* transform;
	CShape* shape;
	CScore* score;
	CRotation* rotation;
	CBoundingBox* boundingBox;
	CMovement* movement;
};