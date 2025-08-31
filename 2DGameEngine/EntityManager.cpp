#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::CreateEntity(const std::string& name, EntityType type) {
	auto entity = std::shared_ptr<Entity>(new Entity(++m_totalEntitiesCreated, name, type));
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
	for (auto entity : m_entitiesToBeAdded) {
		m_entities.push_back(entity);
	}
	m_entitiesToBeAdded.clear();

	auto newEnd = std::remove_if(m_entities.begin(), m_entities.end(), [](std::shared_ptr<Entity> entity) {
		return !entity->isActive();
	});
	m_entities.erase(newEnd, m_entities.end());
}