#include "MenuScene.h"

MenuScene::MenuScene(Window &window) : window(window) {}

void MenuScene::init() {}

void MenuScene::update() {
  entityManager.update();

  sRender();
}

void MenuScene::sRender() {
  window.drawRect(100, 100, 100, 100, {255, 100, 0});

  window.render();
}
