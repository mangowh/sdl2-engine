#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	for (auto& e : m_toAdd) {
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	for (auto& e : m_entities) {
		// TODO remove dead entities
	}
	m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto newEntity = std::make_shared<Entity>(tag, m_totalEntities++);
	m_entities.push_back(newEntity);
	m_entityMap[tag].push_back(newEntity);
	return newEntity;
}

EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}
