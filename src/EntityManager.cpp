#include "EntityManager.h"

EntityManager::EntityManager() {}

void EntityManager::update() {
  for (auto &e : m_toAdd) {
    m_entities.push_back(e);
    m_entityMap[e->tag()].push_back(e);
  }
  for (auto &e : m_entities) {
    if (e) {
      if (!e->isActive()) {
        removeEntity(e);
      }
    }
  }
  m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const EntityType tag) {
  auto newEntity = std::make_shared<Entity>(tag, m_totalEntities++);
  m_toAdd.push_back(newEntity);
  return newEntity;
}

EntityVec &EntityManager::getEntities() { return m_entities; }

EntityVec &EntityManager::getEntities(const EntityType tag) {
  return m_entityMap[tag];
}

void EntityManager::removeEntity(std::shared_ptr<Entity> e) {
  m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
                                  [&](const std::shared_ptr<Entity> _e) {
                                    return e->id() == _e->id();
                                  }),
                   m_entities.end());

  m_entityMap[e->tag()].erase(
      std::remove_if(m_entityMap[e->tag()].begin(), m_entityMap[e->tag()].end(),
                     [&](const std::shared_ptr<Entity> _e) {
                       return e->id() == _e->id();
                     }),
      m_entityMap[e->tag()].end());
}