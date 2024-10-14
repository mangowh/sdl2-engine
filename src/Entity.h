#ifndef ENTITY_H
#define ENTITY_H

#include "CTransform.h"
#include "CShape.h"

#include <string>
#include <memory>

class Entity
{
	const int m_id = 0;
	/** Entity type. TODO create enum*/
	const std::string m_tag = "Default";
	bool m_active = true;

public:
	Entity(const std::string& tag, int id);

	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	//std::shared_ptr<CCollision> cCollision;
	//std::shared_ptr<CInput> cInput;
	//std::shared_ptr<CScore> cScore;
	//std::shared_ptr<cLifespan> cLifespan;

	int id() const { return m_id; }
	auto tag() const { return m_tag; }
	bool isActive() const { return m_active; }
	void destroy();
};

#endif // ENTITY_H