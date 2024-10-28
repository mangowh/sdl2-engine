#pragma once

#include "../Engine.h"
#include "../Random.h"
#include "../window.h"
#include "Scene.h"

class GeometryWarsScene : public Scene {
public:
  GeometryWarsScene(Window &window);

  void init() override;
  void update() override;

private:
  int currentFrame = 0;

  Window &window;
  //Engine &Engine;

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
  void spawnProjectile(Vector2 direction);
  void specialMove(Vector2 position);
};
