#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<EntityType, EntityVec> EntityMap;

class EntityManager {
  EntityVec m_entities;
  EntityMap m_entityMap;
  EntityVec m_toAdd;

  int m_totalEntities = 0;

public:
  EntityManager();

  void init();
  void update();

  std::shared_ptr<Entity> addEntity(const EntityType tag);
  EntityVec &getEntities();
  EntityVec &getEntities(EntityType tag);

  void removeEntity(std::shared_ptr<Entity> e);
};

#endif // ENTITY_MANAGER_H