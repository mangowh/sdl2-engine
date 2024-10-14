#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	for (auto &e : m_toAdd) {
		m_entities.push_back(e);
		//m_entityMap[e->tag()].push_back(e);
	}
	for (auto &e : m_entities) {
		// todo
	}
	m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto newEntity = std::make_shared<Entity>(tag, this->m_totalEntities++);

	this->m_entities.push_back(newEntity);
	this->m_entityMap[tag].push_back(newEntity);

	return newEntity;
}