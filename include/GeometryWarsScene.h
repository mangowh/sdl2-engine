#pragma once

#include "Scene.h"
#include "Window.h"

extern Window window;

class GeometryWarsScene : public Scene {
public:
  GeometryWarsScene();

  void init() override;
  void update() override;

private:
  int currentFrame = 0;

  std::shared_ptr<Entity> player;

  void sUserInput();
  void sMovement();
  void sCollision();
  void sLifespan();
  void sEnemySpawner();
  void sRender();

  bool checkCollision(std::shared_ptr<CCollision> c1,
                      std::shared_ptr<CCollision> c2);

  void setWorldBoundaries();
  void spawnPlayer();
  void spawnEnemy();
  void spawnProjectile(Physics::Vector2 direction);
  void specialMove(Physics::Vector2 position);
};
