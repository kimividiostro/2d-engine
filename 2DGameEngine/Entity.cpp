#include "Entity.h"

Entity::Entity(int id, EntityType type) 
    : m_id(id), m_type(type) {
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

const int Entity::getId() {
    return m_id;
}

Entity::~Entity() {
    delete transform;
    delete shape;
    delete score;
    delete rotation;
    delete boundingBox;
    delete movement;
}