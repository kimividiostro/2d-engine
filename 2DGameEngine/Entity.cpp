#include "Entity.h"

Entity::Entity(int id, const std::string& name, EntityType type) 
    : m_id(id), m_name(name), m_type(type) {
}

bool Entity::isActive() {
    return m_active;
}

void Entity::destroy() {
    m_active = false;
}

const EntityType Entity::getType() {
    return m_type;
}

const std::string& Entity::getName() {
    return m_name;
}

const int Entity::getId() {
    return m_id;
}