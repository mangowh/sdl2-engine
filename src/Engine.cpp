#include "Engine.h"

Engine::Engine()
{
	player = entityManager.addEntity("player");
	player->cTransform = std::make_shared<CTransform>(CTransform({ 100, 100 }, { 0,0 }));
	player->cShape = std::make_shared<CShape>();
	player->cShape->type = "rect";

	auto circle = entityManager.addEntity("enemy");
	circle->cTransform = std::make_shared<CTransform>(CTransform({ 100, 20 }, { 0.001, 0.004 }));
	circle->cShape = std::make_shared<CShape>();

	auto circle2 = entityManager.addEntity("enemy");
	circle2->cTransform = std::make_shared<CTransform>(CTransform({ 100, 200 }, { -0.01, 0.004 }));
	circle2->cShape = std::make_shared<CShape>();

	window.addCallback([&]()
		{
			entityManager.update();

			sMovement();
			sUserInput();
			sRender();

			m_currentFrame++;
		});

	window.open();
}

void Engine::mainLoop()
{
	this->entityManager.update();
}

void Engine::sMovement()
{
	for (auto& e : entityManager.getEntities())
	{
		if (e->cTransform) {
			e->cTransform->pos.x += e->cTransform->velocity.x;
			e->cTransform->pos.y += e->cTransform->velocity.y;
		}
	}
}

void Engine::sUserInput()
{
	auto keyboardState = window.keyboardState;

	// Check if specific keys are pressed
	// TODO remove SDL references in Engine
	if (keyboardState[SDL_SCANCODE_UP]) {
		player->cTransform->velocity.y = -0.1;
	}
	else if (keyboardState[SDL_SCANCODE_DOWN])
	{
		player->cTransform->velocity.y = 0.1;
	}
	else
	{
		player->cTransform->velocity.y = 0;
	}

	if (keyboardState[SDL_SCANCODE_LEFT]) {
		player->cTransform->velocity.x = -0.1;
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		player->cTransform->velocity.x = 0.1;
	}
	else
	{
		player->cTransform->velocity.x = 0;
	}
}

void Engine::sRender()
{
	window.clear();

	for (auto& e : entityManager.getEntities()) {

		if (e->cTransform && e->cShape)
		{
			window.drawShape(e->cTransform, e->cShape);
		}

	}

	window.draw();
}
