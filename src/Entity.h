#ifndef ENTITY_H
#define ENTITY_H

#include "Physics.h"

#include <string>
#include <memory>

class Entity
{
	const int m_id = 0;
	const std::string m_tag = "Default";
	bool m_alive = true;

public:
	std::shared_ptr<CTransform> cTransform;

	Entity(const std::string& tag, int id);
};

#endif