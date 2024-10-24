#ifndef ENGINE_H
#define ENGINE_H

#include "EntityManager.h"
#include "Random.h"
#include "Window.h"

struct Config {
  float playerSpeed{10.0f};
};

class Engine {
  Config config;

  Window window;
  EntityManager entityManager;

  // systems
  void sMovement();
  void sCollision();
  void sUserInput();
  void sLifespan();
  void sEnemySpawner();
  void sRender();

  bool checkCollision(std::shared_ptr<CCollision> c1,
                      std::shared_ptr<CCollision> c2);

  // font & text

  std::shared_ptr<Entity> player;

  int currentFrame = 0;

  bool paused = false;

  // various configurations

public:
  Engine(Config config = {});

  void init();
  void update();

  void run();
  void pause();

  void setWorldBoundaries();
  void spawnPlayer();
  void spawnEnemy();
  void spawnProjectile(Vector2 direction);
  void specialMove(Vector2 position);

  auto isRunning() { return paused; }
};

#endif // !ENGINE_H
