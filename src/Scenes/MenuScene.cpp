#include "MenuScene.h"

MenuScene::MenuScene() {}

MenuScene::~MenuScene() {}

void MenuScene::init() {
  const auto &option1 = entityManager.addEntity(EntityType::text);
  option1->cTransform = std::make_shared<CTransform>(Physics::Vector2({100, 100}));
  option1->cText = std::make_shared<CText>("Scene 1");
  options.push_back(option1);

  const auto &option2 = entityManager.addEntity(EntityType::text);
  option2->cTransform =
      std::make_shared<CTransform>(Physics::Vector2({100, 200}));
  option2->cText = std::make_shared<CText>("Scene 2");
  options.push_back(option2);

  const auto &option3 = entityManager.addEntity(EntityType::text);
  option3->cTransform =
      std::make_shared<CTransform>(Physics::Vector2({100, 300}));
  option3->cText = std::make_shared<CText>("Scene 3");
  options.push_back(option3);

  actionManager.registerSubscriber(ActionName::top, [&](Action action) {
    // if (action.getType() == ActionType::end) {
    currentSelectedOption--;
    if (currentSelectedOption < 0) {
      currentSelectedOption = options.size() - 1;
    }

    for (auto &o : options) {
      o->cText->color = {255, 255, 255};
    }
    //}
  });

  actionManager.registerSubscriber(ActionName::bottom, [&](Action action) {
    // if (action.getType() == ActionType::end) {
    currentSelectedOption++;
    if (currentSelectedOption > options.size() - 1) {
      currentSelectedOption = 0;
    }

    for (auto &o : options) {
      o->cText->color = {255, 255, 255};
    }

    //}
  });

  actionManager.registerSubscriber(ActionName::confirm, [&](Action action) {
    sceneManager.setCurrentScene(currentSelectedOption + 1);
  });

  actionManager.registerSubscriber(ActionName::esc, [&](Action action) { window.shouldQuit = true;
  });
}

void MenuScene::update() {
  entityManager.update();

  // text loading system
  const auto &text = entityManager.getEntities(EntityType::text);

  for (auto &t : text) {
    if (t->cText->textObj == NULL) {
      Text text{window.getRenderer(), t->cText->text};
      t->cText->textObj = std::make_shared<Text>(text);
    } else {
      options[currentSelectedOption]->cText->color = {255, 100, 0};

      t->cText->textObj->setColor(t->cText->color);
    }
  }

  sRender();
}

void MenuScene::sRender() {
  const auto &text = entityManager.getEntities(EntityType::text);

  for (auto &t : text) {
    if (t->cText->textObj) {
      t->cText->textObj->draw(t->cTransform->position.x,
                              t->cTransform->position.y);
    }
  }

  window.render();
}
