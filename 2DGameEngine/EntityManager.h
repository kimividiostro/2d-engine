#pragma once

#include"Entity.h"
#include<vector>
#include<memory>
#include<map>

typedef std::vector<Entity*> EntityVector;
typedef std::map<EntityType, EntityVector> EntityMap;

class EntityManager {
public:
	EntityVector m_entities;
	EntityVector m_entitiesToBeAdded;
	EntityMap m_entityMap;
	int m_totalEntitiesCreated = 0;

	Entity* CreateEntity(EntityType type = DEFAULT);
	void RemoveEntity(Entity* entity);
	EntityVector& GetAllEntities();
	EntityVector& GetEntitiesByType(EntityType type);
	void Update();
};