#include "MegamarioScene.h"

#include "../Physics.h"

#include <iomanip>
#include <sstream>

#include <SDL.h>

void MegamarioScene::init() {
  player = entityManager.addEntity(EntityType::player);
  const Physics::Vector2 initialPos{300, 300};
  player->cTransform = std::make_shared<CTransform>(initialPos);
  player->cSprite = std::make_shared<CSprite>(window.getRenderer());
  player->cCollision =
      std::make_shared<CCollision>(initialPos, initialPos + 60);

  // load map data
  sol::state lua;

  sol::protected_function_result res = lua.script_file("scripts/map.lua");

  if (res.valid()) {
    sol::table map = res;
    sol::table layers = map["layers"];

    for (const auto &layer_pair : layers) {
      sol::table layer = layer_pair.second;
      sol::table data = layer["data"];

      tilemap = entityManager.addEntity(EntityType::tilemap);
      tilemap->cTilemap = std::make_shared<CTilemap>();

      const auto size = tilemap->cTilemap->size;
      const auto tilesOnRow = window.getWidth() / size;

      const auto &properties = layer["properties"];
      const bool &isCollision = properties["collision"].get_or(false);

      for (const auto &data_pair : data) {
        const auto i = data_pair.first.as<int>();
        const auto value = data_pair.second.as<int>();
        if (value != 0) {
          std::stringstream ss;
          ss << std::setw(4) << std::setfill('0') << value - 1;
          std::string s = ss.str();

          std::string path = "./assets/tiles/tile_" + s + ".png";

          Texture t{window.getRenderer(), path};

          const auto x = (i - 1) % tilesOnRow;
          const auto y = (i - 1) / tilesOnRow;

          std::cout << x << " : " << y << std::endl;

          const Physics::Vector2 tilePos{x * size, y * size};
          tilemap->cTilemap->tiles.push_back({tilePos, t});

          if (isCollision) {
            const CCollision collision{tilePos, tilePos + size};

            tilemap->cTilemap->collision.push_back({tilePos, collision});
          }
        }
      }
    }
  }
}

void MegamarioScene::update() {
  entityManager.update();

  const auto &entities = entityManager.getEntities();
  for (auto &e : entities) {
    if (e->cTransform) {
      if (e->cCollision) {
        for (auto &e2 : entities) {
          if (e->tag() == EntityType::player) {
            if (e2->tag() == EntityType::tilemap) {
              for (auto &colliderData : e2->cTilemap->collision) {
                const auto &c = *e->cCollision;
                const auto c2 = colliderData.second;

                const Physics::Rect r{c.p1, c.p2};
                const Physics::Rect r2{c2.p1, c2.p2};

                const auto colliding = Physics::checkCollision(r, r2);

                if (colliding) {
                  if (c.center.x < c2.center.x) {
                    if (player->cTransform->velocity.x < 0) {
                      player->cTransform->velocity.x = 0;
                    }
                  } else if (c.center.x < c2.center.x) {
                    if (player->cTransform->velocity.x > 0) {
                      player->cTransform->velocity.x = 0;
                    }
                  } else if (c.center.y > c2.center.y) {
                    if (player->cTransform->velocity.y < 0) {
                      player->cTransform->velocity.y = 0;
                    }
                  } else if (c.center.y < c2.center.y) {
                    if (player->cTransform->velocity.y > 0) {
                      player->cTransform->velocity.y = 0;
                    }
                  }
                }
              }
            }
          }
        }
      }

      e->cTransform->previousPosition = e->cTransform->position;

      e->cTransform->position.x += e->cTransform->velocity.x;
      e->cTransform->position.y += e->cTransform->velocity.y;

      if (e->cCollision->shape == ColliderShape::rect) {
        e->cCollision->p1 += e->cTransform->velocity;
        e->cCollision->p2 += e->cTransform->velocity;
      }

      e->cCollision->center.x += e->cTransform->velocity.x;
      e->cCollision->center.y += e->cTransform->velocity.y;
    }
  }

  sUserInput();

  sRender();
}

void MegamarioScene::sUserInput() {
  auto keyboardState = window.keyboardState;

  const int playerSpeed = 10;

  if (keyboardState[SDL_SCANCODE_W]) {
    player->cTransform->velocity.y = -playerSpeed;
  } else if (keyboardState[SDL_SCANCODE_S]) {
    player->cTransform->velocity.y = playerSpeed;
  } else {
    player->cTransform->velocity.y = 0;
  }

  if (keyboardState[SDL_SCANCODE_A]) {
    player->cTransform->velocity.x = -playerSpeed;
  } else if (keyboardState[SDL_SCANCODE_D]) {
    player->cTransform->velocity.x = playerSpeed;
  } else {
    player->cTransform->velocity.x = 0;
  }
}

void MegamarioScene::sRender() {
  window.clear();

  for (auto &e : entityManager.getEntities()) {
    if (e->cTilemap) {
      for (int i = 0; i < e->cTilemap->tiles.size(); i++) {
        const auto size = tilemap->cTilemap->size;

        const auto &tileInfo = e->cTilemap->tiles[i];
        const auto &pos = tileInfo.first;
        const auto &texture = tileInfo.second;

        SDL_Rect dstRect = {static_cast<int>(pos.x), static_cast<int>(pos.y),
                            static_cast<int>(size), static_cast<int>(size)};

        SDL_RenderCopy(window.getRenderer(), (SDL_Texture *)texture.texture,
                       NULL, &dstRect);
      }
    }

    if (e->cTransform && e->cShape) {
      window.drawShape(e->cTransform, e->cShape);
    }

    if (e->cTransform && e->cSprite) {
      // Set the destination rectangle for the sprite
      SDL_Rect dstRect = {static_cast<int>(e->cTransform->position.x),
                          static_cast<int>(e->cTransform->position.y),
                          e->cSprite->width, e->cSprite->height};

      // Render the sprite
      SDL_RenderCopy(window.getRenderer(), e->cSprite->getTexture(), NULL,
                     &dstRect);
    }

    window.drawDebug(e);
  }

  window.render();
}
