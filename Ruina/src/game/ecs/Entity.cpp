#include "Entity.h"
#include <iostream>

Entity::Entity(EntityId id, EntityType type) : m_id(id), m_type(type) {};

Speaker::Speaker(EntityId id, EntityType type) : Entity(id, type) {
	std::cout << "Logged something :DDD" << std::endl;
}
