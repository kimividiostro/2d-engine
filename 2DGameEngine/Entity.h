#pragma once
#include <string>

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
	const std::string m_name;
	EntityType m_type = DEFAULT;
	bool m_active = true;
	Entity(int id, const std::string& name, EntityType type);

public:
	bool isActive();
	const EntityType getType();
	const std::string& getName();
	const int getId();
	void destroy();
};