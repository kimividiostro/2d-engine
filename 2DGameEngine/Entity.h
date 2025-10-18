#pragma once
#include <string>
#include "Components.h"

enum EntityType {
	DEFAULT,
	PLAYER,
	ENEMY,
	PROJECTILE,
	POWERUP
};

class Entity {
	friend class EntityManager;

	const int m_id;
	EntityType m_type = DEFAULT;
	bool m_active = true;
	Entity(int id, EntityType type);
	void destroy();

public:
	bool isActive();
	const EntityType getType();
	const int getId();

	std::shared_ptr<CTransform> transform;
	std::shared_ptr<CShape> shape;
	std::shared_ptr<CScore> score;
	std::shared_ptr<CRotation> rotation;
	std::shared_ptr<CBoundingBox> boundingBox;
};