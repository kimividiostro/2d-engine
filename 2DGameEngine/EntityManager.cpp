#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::CreateEntity(EntityType type) {
	auto entity = std::shared_ptr<Entity>(new Entity(++m_totalEntitiesCreated, type));
	m_entitiesToBeAdded.push_back(entity);
	m_entityMap[type].push_back(entity);
	return entity;
}

EntityVector& EntityManager::GetAllEntities() {
	return m_entities;
}

EntityVector& EntityManager::GetEntitiesByType(EntityType type) {
	return m_entityMap[type];
}

void EntityManager::RemoveEntity(std::shared_ptr<Entity> entity) {
	entity->destroy();
}

void EntityManager::Update() {
	if (m_entitiesToBeAdded.size() > 0) {
		for (auto entity : m_entitiesToBeAdded) {
			m_entities.push_back(entity);
		}
		m_entitiesToBeAdded.clear();
	}

	//TODO: Optimize removing so it doesn't have to loop through all entities each frame
	auto newEnd = std::remove_if(m_entities.begin(), m_entities.end(), [](std::shared_ptr<Entity> entity) {
		return !entity->isActive();
	});
	m_entities.erase(newEnd, m_entities.end());

	for (auto& tag : m_entityMap) {
		auto& entities = tag.second;
		auto newEnd = std::remove_if(entities.begin(), entities.end(), [](std::shared_ptr<Entity> entity) {
			return !entity->isActive();
			});
		entities.erase(newEnd, entities.end());
	}
}