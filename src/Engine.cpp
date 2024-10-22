#include "Engine.h"

Engine::Engine(Config config) : config(config) { init(); }

void Engine::init() {
  window.addCallback([&]() {
    entityManager.update();

    sUserInput();

    if (!paused) {
      sCollision();
      sMovement();
      sLifespan();
      sEnemySpawner();
    }

    sRender();

    currentFrame++;
  });

  window.onClick = [&](Vector2 coords) { spawnProjectile(coords); };

  window.onRightClick = [&](Vector2 coords) { specialMove(coords); };

  spawnPlayer();

  { window.open(); }
}

void Engine::run() { paused = false; }

void Engine::pause() { paused = true; }

void Engine::spawnPlayer() {
  Vector2 centerOfScreen = {(window.getWidth() - 100) / 2.0f,
                            (window.getHeight() - 100) / 2.0f};

  player = entityManager.addEntity(EntityType::player);
  player->cTransform = std::make_shared<CTransform>(centerOfScreen);
  player->cShape = std::make_shared<CShape>(CShape(100, 100, {255, 100, 0}));
  player->cCollision =
      std::make_shared<CCollision>(centerOfScreen + 50, 100 / 2.0f);
}

void Engine::spawnEnemy() {
  Random rand;

  Vector2 pos = {(float)rand.genRandomInt(0, window.getWidth()),
                 (float)rand.genRandomInt(0, window.getHeight())};

  auto enemy = entityManager.addEntity(EntityType::enemy);
  enemy->cTransform = std::make_shared<CTransform>(
      CTransform(pos, {(rand.genRandomInt(1, 200) - 100) / 10.0f,
                       (rand.genRandomInt(1, 200) - 100) / 10.0f}));

  enemy->cShape = std::make_shared<CShape>(CShape(
      50, 50,
      {(uint8_t)rand.genRandomInt(0, 255), (uint8_t)rand.genRandomInt(0, 255),
       (uint8_t)rand.genRandomInt(0, 255)}));
  enemy->cCollision = std::make_shared<CCollision>(pos + 50 / 2.0f, 50 / 2.0f);
}

void Engine::spawnProjectile(Vector2 direction) {
  Random rand;

  auto playerPosition = player->cTransform->pos;

  Vector2 playerCenter =
      Vector2(playerPosition.x + 100 / 2, playerPosition.y + 100 / 2.0f);
  auto directionFromPlayer = direction - playerCenter;

  auto projectile = entityManager.addEntity(EntityType::projectile);
  projectile->cTransform = std::make_shared<CTransform>(
      CTransform(playerCenter, directionFromPlayer.normalized() * 20));

  const Color randomColor = {(uint8_t)rand.genRandomInt(0, 255),
                             (uint8_t)rand.genRandomInt(0, 255),
                             (uint8_t)rand.genRandomInt(0, 255)};

  const int dimension = 50;

  Vector2 v1 = Vector2(playerCenter.x + dimension / 2, playerCenter.y);
  Vector2 v2 = Vector2(playerCenter.x, playerCenter.y + dimension);
  Vector2 v3 = Vector2(playerCenter.x + dimension, playerCenter.y + dimension);

  v1 -= dimension / 2;
  v2 -= dimension / 2;
  v3 -= dimension / 2;

  projectile->cShape =
      std::make_shared<CShape>(CShape(v1, v2, v3, randomColor));
  projectile->cCollision =
      std::make_shared<CCollision>(playerCenter, dimension / 2.0f);
  projectile->cLifespan = std::make_shared<CLifespan>(100);
}

void Engine::specialMove(Vector2 position) {
  const int dimension = 100;

  auto projectile = entityManager.addEntity(EntityType::projectile);
  projectile->cTransform =
      std::make_shared<CTransform>(CTransform(position - dimension / 2.0f));

  const Color color = {255, 34, 22};

  projectile->cShape =
      std::make_shared<CShape>(CShape(dimension, dimension, color));
  projectile->cCollision =
      std::make_shared<CCollision>(position, dimension / 2.0f);
  projectile->cLifespan = std::make_shared<CLifespan>(50);
}

void Engine::sMovement() {
  for (auto &e : entityManager.getEntities()) {
    if (e->cTransform) {
      e->cTransform->pos.x += e->cTransform->velocity.x;
      e->cTransform->pos.y += e->cTransform->velocity.y;

      if (e->cShape) {
        // translate triangles
        for (auto &v : e->cShape->verts) {
          v += e->cTransform->velocity;
        }
      }

      if (e->cCollision) {
        e->cCollision->center.x += e->cTransform->velocity.x;
        e->cCollision->center.y += e->cTransform->velocity.y;
      }
    }
  }
}

void Engine::sCollision() {
  for (auto &e : entityManager.getEntities()) {
    if (e->cCollision && e->cTransform)

      // Screen border collision
      if (e->tag() == EntityType::player) {
        if (e->cCollision->center.x - e->cCollision->radius < 0 &&
            e->cTransform->velocity.x < 0) {
          e->cTransform->velocity.x = 0.0f;
        }

        const int windowW = window.getWidth();
        if (e->cCollision->center.x + e->cCollision->radius > windowW &&
            e->cTransform->velocity.x > 0) {
          e->cTransform->velocity.x = 0.0f;
        }

        if (e->cCollision->center.y - e->cCollision->radius < 0 &&
            e->cTransform->velocity.y < 0) {
          e->cTransform->velocity.y = 0.0f;
        }

        const int windowH = window.getHeight();
        if (e->cCollision->center.y + e->cCollision->radius > windowH &&
            e->cTransform->velocity.y > 0) {
          e->cTransform->velocity.y = 0.0f;
        }
      }

    // Enemy bouncing
    if (e->tag() == EntityType::enemy) {
      if (e->cCollision->center.x - e->cCollision->radius < 0 &&
          e->cTransform->velocity.x < 0) {
        e->cTransform->velocity.x = -e->cTransform->velocity.x;
      }

      const int windowW = window.getWidth();
      if (e->cCollision->center.x + e->cCollision->radius > windowW &&
          e->cTransform->velocity.x > 0) {
        e->cTransform->velocity.x = -e->cTransform->velocity.x;
      }

      if (e->cCollision->center.y - e->cCollision->radius < 0 &&
          e->cTransform->velocity.y < 0) {
        e->cTransform->velocity.y = -e->cTransform->velocity.y;
      }

      const int windowH = window.getHeight();
      if (e->cCollision->center.y + e->cCollision->radius > windowH &&
          e->cTransform->velocity.y > 0) {
        e->cTransform->velocity.y = -e->cTransform->velocity.y;
      }
    }

    // Projectile / Enemy collision
    if (e->tag() == EntityType::projectile) {
      const auto projCollider = e->cCollision;

      for (auto &enemy : entityManager.getEntities(EntityType::enemy)) {
        const auto enemyCollider = enemy->cCollision;

        if ((projCollider->center - enemyCollider->center).magnitude() <
            projCollider->radius + enemyCollider->radius) {
          enemy->destroy();
        }
      }
    }

    // Player / Projectile collsion
    if (e->tag() == EntityType::player) {
      const auto playerCollider = e->cCollision;

      for (auto &enemy : entityManager.getEntities(EntityType::enemy)) {
        const auto enemyCollider = enemy->cCollision;

        if ((playerCollider->center - enemyCollider->center).magnitude() <
            playerCollider->radius + enemyCollider->radius) {
          enemy->destroy();
          player->destroy();
          spawnPlayer();
          break;
        }
      }
    }
  }
}

void Engine::sUserInput() {
  // TODO remove SDL references in Engine

  auto keyboardState = window.keyboardState;

  // Player movement
  if (keyboardState[SDL_SCANCODE_W]) {
    player->cTransform->velocity.y = -config.playerSpeed;
  } else if (keyboardState[SDL_SCANCODE_S]) {
    player->cTransform->velocity.y = config.playerSpeed;
  } else {
    player->cTransform->velocity.y = 0;
  }

  if (keyboardState[SDL_SCANCODE_A]) {
    player->cTransform->velocity.x = -config.playerSpeed;
  } else if (keyboardState[SDL_SCANCODE_D]) {
    player->cTransform->velocity.x = config.playerSpeed;
  } else {
    player->cTransform->velocity.x = 0;
  }

  // Pause
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_P]) {
    if (!paused) {
      pause();
    } else {
      run();
    }
  }

  // Fullscreen
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_F]) {
    window.setFullscreen();
  }
}

void Engine::sLifespan() {
  for (auto &e : entityManager.getEntities()) {
    if (e->cLifespan) {
      e->cLifespan->remaining--;

      if (e->cLifespan->remaining <= 0) {
        e->destroy();
      }
    }
  }
}

void Engine::sEnemySpawner() {
  if (currentFrame % 100 == 0) {
    spawnEnemy();
  }
}

void Engine::sRender() {
  window.clear();

  for (auto &e : entityManager.getEntities()) {

    if (e->cTransform && e->cShape) {
      window.drawShape(e->cTransform, e->cShape);
    }

    window.drawDebug(e);
  }

  window.render();
}
