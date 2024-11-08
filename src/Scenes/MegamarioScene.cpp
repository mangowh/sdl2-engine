#include "MegamarioScene.h"

#include <iomanip>
#include <sstream>

void MegamarioScene::init() {
  player = entityManager.addEntity(EntityType::player);
  player->cTransform = std::make_shared<CTransform>(Vector2(300, 300));
  player->cSprite = std::make_shared<CSprite>(window.getRenderer());

  tilemap = entityManager.addEntity(EntityType::tilemap);
  tilemap->cTilemap = std::make_shared<CTilemap>();

  // load map data
  sol::state lua;

  sol::protected_function_result res = lua.script_file("scripts/map.lua");

  if (res.valid()) {
    sol::table map = res;
    sol::table data = map["layers"][1]["data"];

    const auto size = tilemap->cTilemap->size;
    const auto tilesOnRow = window.getWidth() / size;

    for (int i = 1; i < data.size(); i++) {
      if (data[i] != 0) {
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << (int)data[i] - 1;
        std::string s = ss.str();

        std::string path = "./assets/tiles/tile_" + s + ".png";

        Texture t{window.getRenderer(), path};

        const auto x = (float)((i - 1) % tilesOnRow);
        const auto y = (float)((i - 1) / tilesOnRow);
        std::cout << x << " : " << y << std::endl;
        tilemap->cTilemap->tiles.push_back({Vector2{x * size, y * size}, t});
      }
    }
  }
}

void MegamarioScene::update() {
  entityManager.update();

  sRender();
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

        SDL_Rect dstRect = {pos.x, pos.y, size, size};

        SDL_RenderCopy(window.getRenderer(), (SDL_Texture *)texture.texture,
                       NULL, &dstRect);
      }
    }

    if (e->cTransform && e->cShape) {
      window.drawShape(e->cTransform, e->cShape);
    }

    if (e->cTransform && e->cSprite) {
      // Set the destination rectangle for the sprite
      SDL_Rect dstRect = {e->cTransform->position.x, e->cTransform->position.y,
                          e->cSprite->width, e->cSprite->height};

      // Render the sprite
      SDL_RenderCopy(window.getRenderer(), e->cSprite->getTexture(), NULL,
                     &dstRect);
    }

    window.drawDebug(e);
  }

  window.render();
}
