#include "GeometryWarsScene.h"

#include "Random.h"

GeometryWarsScene::GeometryWarsScene() {}

void GeometryWarsScene::init() {
  setWorldBoundaries();

  spawnPlayer();

  gWindow.onClick = [&](Physics::Vector2 coords) { spawnProjectile(coords); };

  gWindow.onRightClick = [&](Physics::Vector2 coords) { specialMove(coords); };

  gActionManager.registerSubscriber(ActionName::esc, [&](Action) {
    // TODO go back
  });
}

void GeometryWarsScene::update() {
  entityManager.update();

  sUserInput();
  sCollision();
  sMovement();
  sLifespan();
  sEnemySpawner();

  sRender();

  currentFrame++;
}

void GeometryWarsScene::sUserInput() {
  auto keyboardState = gWindow.keyboardState;

  const int playerSpeed = 10;

  if (keyboardState[SDL_SCANCODE_W]) {
    player->cTransform->velocity.y = -playerSpeed;
  } else if (keyboardState[SDL_SCANCODE_S]) {
    player->cTransform->velocity.y = playerSpeed;
  } else {
    player->cTransform->velocity.y = 0;

    if (keyboardState[SDL_SCANCODE_A]) {
      player->cTransform->velocity.x = -playerSpeed;
    } else if (keyboardState[SDL_SCANCODE_D]) {
      player->cTransform->velocity.x = playerSpeed;
    } else {
      player->cTransform->velocity.x = 0;
    }
  }
}

void GeometryWarsScene::sMovement() {
  for (auto &e : entityManager.getEntities()) {
    if (e->cTransform) {
      e->cTransform->previousPosition = e->cTransform->position;

      e->cTransform->position.x += e->cTransform->velocity.x;
      e->cTransform->position.y += e->cTransform->velocity.y;

      if (e->cShape) {
        // translate triangles
        if (e->cShape->type == ShapeType::triangle) {
          for (auto &v : e->cShape->verts) {
            v += e->cTransform->velocity;
          }
        }
      }

      if (e->cCollision) {
        if (e->cCollision->shape == ColliderShape::rect) {
          e->cCollision->p1 += e->cTransform->velocity;
          e->cCollision->p2 += e->cTransform->velocity;
        }

        e->cCollision->center.x += e->cTransform->velocity.x;
        e->cCollision->center.y += e->cTransform->velocity.y;
      }
    }
  }
}

void GeometryWarsScene::sCollision() {
  const auto &entities = entityManager.getEntities();

  for (auto &e1 : entities) {
    for (auto &e2 : entities) {
      if ((e1->cTransform && e1->cCollision) &&
          (e2->cTransform && e2->cCollision)) {
        if (e1->id() != e2->id()) {
          // Player / Projectile collision
          if (e1->tag() == EntityType::player &&
              e2->tag() == EntityType::enemy) {
            const auto &enemy = e2;
            const auto collision =
                checkCollision(e1->cCollision, e2->cCollision);

            if (collision) {
              enemy->destroy();
              player->destroy();

              spawnPlayer();
              break;
            }
          }

          // Projectile / Enemy collision
          if (e1->tag() == EntityType::projectile &&
              e2->tag() == EntityType::enemy) {
            const auto collision =
                checkCollision(e1->cCollision, e2->cCollision);

            if (collision) {
              e2->destroy();
            }
          }

          // Boundary collision
          if (e1->tag() == EntityType::boundary &&
              e2->tag() != EntityType::boundary) {
            const auto collision =
                checkCollision(e1->cCollision, e2->cCollision);

            if (collision) {
              // todo rework
              if (e1->cCollision->center.x <
                      e2->cTransform->previousPosition.x &&
                  e2->cTransform->velocity.x < 0) {
                if (e2->tag() == EntityType::enemy) {
                  e2->cTransform->velocity.x = -e2->cTransform->velocity.x;
                } else {
                  e2->cTransform->velocity.x = 0;
                }
              } else if (e1->cCollision->center.x >
                             e2->cTransform->previousPosition.x &&
                         e2->cTransform->velocity.x > 0) {
                if (e2->tag() == EntityType::enemy) {
                  e2->cTransform->velocity.x = -e2->cTransform->velocity.x;
                } else {
                  e2->cTransform->velocity.x = 0;
                }
              } else if (e1->cCollision->center.y <
                             e2->cTransform->previousPosition.y &&
                         e2->cTransform->velocity.y < 0) {
                if (e2->tag() == EntityType::enemy) {
                  e2->cTransform->velocity.y = -e2->cTransform->velocity.y;
                } else {
                  e2->cTransform->velocity.y = 0;
                }
              } else if (e1->cCollision->center.y >
                             e2->cTransform->previousPosition.y &&
                         e2->cTransform->velocity.y > 0) {
                if (e2->tag() == EntityType::enemy) {
                  e2->cTransform->velocity.y = -e2->cTransform->velocity.y;
                } else {
                  e2->cTransform->velocity.y = 0;
                }
              }
            }
          }
        }
      }
    }
  }
}

void GeometryWarsScene::sLifespan() {
  for (auto &e : entityManager.getEntities()) {
    if (e->cLifespan) {
      e->cLifespan->remaining--;

      if (e->cLifespan->remaining <= 0) {
        e->destroy();
      }
    }
  }
}

void GeometryWarsScene::sEnemySpawner() {
  if (currentFrame % 100 == 0) {
    spawnEnemy();
  }
}

void GeometryWarsScene::sRender() {
  gWindow.clear();

  for (auto &e : entityManager.getEntities()) {
    if (e->cTransform && e->cShape) {
      gWindow.drawShape(e->cTransform, e->cShape);
    }

    gWindow.drawDebug(e);
  }

  gWindow.render();
}

/**
https://www.jeffreythompson.org/collision-detection/table_of_contents.php
*/
bool GeometryWarsScene::checkCollision(std::shared_ptr<CCollision> c1,
                                       std::shared_ptr<CCollision> c2) {
  if (c1->shape == ColliderShape::circle && c2->shape == ColliderShape::rect) {

    // https://www.jeffreythompson.org/collision-detection/circle-rect.php
    const int cx = c1->center.x;
    const int cy = c1->center.y;
    const int radius = c1->radius;
    const int rx = c2->p1.x;
    const int ry = c2->p1.y;
    const int rw = c2->p2.x - c2->p1.x;
    const int rh = c2->p2.y - c2->p1.y;

    // temporary variables to set edges for testing
    int testX = cx;
    int testY = cy;

    // which edge is closest?
    if (cx < rx)
      testX = rx; // test left edge
    else if (cx > rx + rw)
      testX = rx + rw; // right edge
    if (cy < ry)
      testY = ry; // top edge
    else if (cy > ry + rh)
      testY = ry + rh; // bottom edge

    // get distance from closest edges
    int distX = cx - testX;
    int distY = cy - testY;
    int distance = (int)sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the radius, collision!
    if (distance <= radius) {
      return true;
    }
    return false;
  }

  if (c1->shape == ColliderShape::rect && c2->shape == ColliderShape::rect) {
    int r1x = c1->p1.x;
    int r1y = c1->p1.y;
    int r1w = c1->w();
    int r1h = c1->h();
    int r2x = c2->p1.x;
    int r2y = c2->p1.y;
    int r2w = c2->w();
    int r2h = c2->h();

    // are the sides of one rectangle touching the other?

    if (r1x + r1w >= r2x && // r1 right edge past r2 left
        r1x <= r2x + r2w && // r1 left edge past r2 right
        r1y + r1h >= r2y && // r1 top edge past r2 bottom
        r1y <= r2y + r2h) { // r1 bottom edge past r2 top
      return true;
    }
    return false;
  }

  if (c1->shape == ColliderShape::circle &&
      c2->shape == ColliderShape::circle) {
    return ((c1->center - c2->center).magnitude() < c1->radius + c2->radius);
  }

  return false;
}

void GeometryWarsScene::setWorldBoundaries() {
  const int boundarySize = 10;

  const int windowW = (int)gWindow.getWidth();
  const int windowH = (int)gWindow.getHeight();

  const auto topBoundary = entityManager.addEntity(EntityType::boundary);
  topBoundary->cTransform =
      std::make_shared<CTransform>(Physics::Vector2({0, -boundarySize}));
  topBoundary->cCollision = std::make_shared<CCollision>(
      Physics::Vector2({0, -boundarySize}), Physics::Vector2({windowW, 0}));

  const auto rightBoundary = entityManager.addEntity(EntityType::boundary);
  rightBoundary->cTransform =
      std::make_shared<CTransform>(Physics::Vector2({windowW, 0}));
  rightBoundary->cCollision = std::make_shared<CCollision>(
      Physics::Vector2({windowW, 0}),
      Physics::Vector2({windowW + boundarySize, windowH}));

  const auto bottomBoundary = entityManager.addEntity(EntityType::boundary);
  bottomBoundary->cTransform =
      std::make_shared<CTransform>(Physics::Vector2({0, windowH}));
  bottomBoundary->cCollision = std::make_shared<CCollision>(
      Physics::Vector2({0, windowH}),
      Physics::Vector2({windowW, windowH + boundarySize}));

  const auto leftBoundary = entityManager.addEntity(EntityType::boundary);
  leftBoundary->cTransform =
      std::make_shared<CTransform>(Physics::Vector2({-boundarySize, 0}));
  leftBoundary->cCollision = std::make_shared<CCollision>(
      Physics::Vector2({-boundarySize, 0}), Physics::Vector2({0, windowH}));
}

void GeometryWarsScene::spawnPlayer() {
  Physics::Vector2 centerOfScreen = {(gWindow.getWidth() - 100) / 2,
                                     (gWindow.getHeight() - 100) / 2};

  player = entityManager.addEntity(EntityType::player);
  player->cTransform = std::make_shared<CTransform>(centerOfScreen);
  player->cShape = std::make_shared<CShape>(CShape(100, 100, {255, 100, 0}));
  player->cCollision =
      std::make_shared<CCollision>(centerOfScreen, centerOfScreen + 100);
}

void GeometryWarsScene::spawnEnemy() {
  Physics::Vector2 pos = {(int)Random::genRandomInt(0, gWindow.getWidth()),
                          (int)Random::genRandomInt(0, gWindow.getHeight())};

  auto enemy = entityManager.addEntity(EntityType::enemy);
  enemy->cTransform = std::make_shared<CTransform>(
      CTransform(pos, {(Random::genRandomInt(1, 200) - 100) / 10,
                       (Random::genRandomInt(1, 200) - 100) / 10}));

  enemy->cShape =
      std::make_shared<CShape>(CShape(50, 50,
                                      {(uint8_t)Random::genRandomInt(0, 255),
                                       (uint8_t)Random::genRandomInt(0, 255),
                                       (uint8_t)Random::genRandomInt(0, 255)}));
  enemy->cCollision = std::make_shared<CCollision>(pos, pos + 50);
}

void GeometryWarsScene::spawnProjectile(Physics::Vector2 direction) {
  auto playerPosition = player->cTransform->position;

  Physics::Vector2 playerCenter =
      Physics::Vector2(playerPosition.x + 100 / 2, playerPosition.y + 100 / 2);
  auto directionFromPlayer = direction - playerCenter;

  auto projectile = entityManager.addEntity(EntityType::projectile);
  projectile->cTransform = std::make_shared<CTransform>(
      CTransform(playerCenter, directionFromPlayer.normalized() * 20));

  const int dimension = 50;

  Physics::Vector2 v1 =
      Physics::Vector2(playerCenter.x + dimension / 2, playerCenter.y);
  Physics::Vector2 v2 =
      Physics::Vector2(playerCenter.x, playerCenter.y + dimension);
  Physics::Vector2 v3 =
      Physics::Vector2(playerCenter.x + dimension, playerCenter.y + dimension);

  v1 -= dimension / 2;
  v2 -= dimension / 2;
  v3 -= dimension / 2;

  const Color randomColor = {(uint8_t)Random::genRandomInt(0, 255),
                             (uint8_t)Random::genRandomInt(0, 255),
                             (uint8_t)Random::genRandomInt(0, 255)};
  projectile->cShape =
      std::make_shared<CShape>(CShape(v1, v2, v3, randomColor));
  projectile->cCollision =
      std::make_shared<CCollision>(playerCenter, dimension / 2);
  projectile->cLifespan = std::make_shared<CLifespan>(100);
}

void GeometryWarsScene::specialMove(Physics::Vector2 position) {
  const int dimension = 100;

  auto projectile = entityManager.addEntity(EntityType::projectile);
  projectile->cTransform =
      std::make_shared<CTransform>(CTransform(position - dimension / 2));

  const Color color = {255, 34, 22};

  projectile->cShape =
      std::make_shared<CShape>(CShape(dimension, dimension, color));
  projectile->cCollision =
      std::make_shared<CCollision>(position, dimension / 2);
  projectile->cLifespan = std::make_shared<CLifespan>(50);
}
