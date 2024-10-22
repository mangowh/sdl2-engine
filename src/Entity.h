#ifndef ENTITY_H
#define ENTITY_H

#include "CCollision.h"
#include "CInput.h"
#include "CLifespan.h"
#include "CScore.h"
#include "CShape.h"
#include "CTransform.h"

#include <memory>
#include <string>

enum class EntityType { player, enemy, projectile };

class Entity {
  const int m_id = 0;
  const EntityType m_tag;
  bool m_active = true;

public:
  Entity(const EntityType tag, const int id) : m_tag(tag), m_id(id) {};

  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CCollision> cCollision;
  std::shared_ptr<CInput> cInput;
  std::shared_ptr<CScore> cScore;
  std::shared_ptr<CLifespan> cLifespan;

  auto id() const { return m_id; }
  auto tag() const { return m_tag; }
  auto isActive() const { return m_active; }

  void destroy();
};

#endif // ENTITY_H