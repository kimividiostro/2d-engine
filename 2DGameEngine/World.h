#pragma once
#include"EntityManager.h"
#include"GameplayCollisionSystem.h"
#include"MovementSystem.h"
#include"ComponentStorage.h"
#include"JumpSystem.h"
#include"Components.h"
#include"InputSystem.h"

class World {

private:
	template<typename T>
	ComponentStorage<T>& getComponentStorage();

public:
	World();
	EntityManager m_entityManager;
	GameplayCollisionSystem m_collisionSystem;
	MovementSystem m_movementSystem;
	JumpSystem m_jumpSystem;

	template<typename T>
	void add(EntityID e);

	template<typename T>
	void remove(EntityID e);

	template<typename T>
	bool has(EntityID e);

	template<typename T>
	T& get(EntityID e);

	template<typename... Ts>
	std::vector<EntityID> view();
};


template <typename T>
ComponentStorage<T>& World::getComponentStorage() {
	static ComponentStorage<T> storage;
	return storage;
}

template<typename T>
void World::add(EntityID e) {
	this->getComponentStorage<T>().add(e);
}

template<typename T>
void World::remove(EntityID e) {
	this->getComponentStorage<T>().remove(e);
}

template<typename T>
bool World::has(EntityID e) {
	bool has = this->getComponentStorage<T>().has(e);
	return has;
}

template<typename T>
T& World::get(EntityID e) {
	return this->getComponentStorage<T>().get(e);
}

// a collection of components types
template<typename... Ts>
std::vector<EntityID> World::view() {
	std::vector<EntityID> result;

	// get the storage of the first component
	auto& first = getComponentStorage<std::tuple_element_t<0, std::tuple<Ts...>>>().data;

	for (auto& [entity, _] : first) {
	// check if the entity has all other components, if so, add to vector
		if ((has<Ts>(entity) && ...)) {
			result.push_back(entity);
		}
	}

	return result;
}