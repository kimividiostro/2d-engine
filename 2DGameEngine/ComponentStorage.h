#pragma once
#include"Entity.h"
#include<unordered_map>

template <typename T>
class ComponentStorage {

public:
	// TODO: replace unordered map with something better
	std::unordered_map<EntityID, T> data;
	bool has(EntityID e);

	T& get(EntityID e);

	void add(EntityID e);

	void remove(EntityID e);
};

template<typename T>
bool ComponentStorage<T>::has(EntityID e) {
	return data.find(e) != data.end();
}

template<typename T>
T& ComponentStorage<T>::get(EntityID e) {
	return data.at(e);
}

template<typename T>
void ComponentStorage<T>::add(EntityID e) {
	data[e] = T{};
}

template<typename T>
void ComponentStorage<T>::remove(EntityID e) {
	data.erase(e);
}