#pragma once

#include"Entity.h"
#include<vector>
#include<memory>
#include<map>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<EntityType, EntityVector> EntityMap;

class EntityManager {
public:
	EntityVector m_entities;
	EntityVector m_entitiesToBeAdded;
	EntityMap m_entityMap;
	int m_totalEntitiesCreated = 0;

	std::shared_ptr<Entity> CreateEntity(EntityType type = DEFAULT);
	void RemoveEntity(std::shared_ptr<Entity> entity);
	EntityVector& GetAllEntities();
	EntityVector& GetEntitiesByType(EntityType type);
	void Update();
};