#include "MegamarioScene.h"

void MegamarioScene::init() {}

void MegamarioScene::update() {
  entityManager.update();

  // draw
  window.clear();

  window.render();
}
