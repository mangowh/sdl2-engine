#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

#include <string>
#include <memory>
#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	int m_totalEntities = 0;

public:
	EntityManager();
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVec& getEntities();
	EntityVec& getEntities(const std::string& tag);
};

#endif