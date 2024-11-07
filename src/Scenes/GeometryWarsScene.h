#pragma once

#include "../Random.h"
#include "../Window.h"
//#include "../SceneManager.h"
#include "Scene.h"

extern Window window;
//extern SceneManager SceneManager;

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
  void spawnProjectile(Vector2 direction);
  void specialMove(Vector2 position);
};
