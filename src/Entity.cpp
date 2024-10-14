#include "Entity.h"

Entity::Entity(const std::string& tag, int id)
{
}

void Entity::destroy()
{
	m_active = false;
}
