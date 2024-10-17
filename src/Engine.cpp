#include "Engine.h"

const int PLAYER_SPEED = 3;


Engine::Engine()
{
	init();
}

void Engine::init()
{
	player = entityManager.addEntity(EntityType::player);
	player->cTransform = std::make_shared<CTransform>(CTransform({ 100, 100 }));
	player->cShape = std::make_shared<CShape>(CShape(100, 100, { 255,100,0 }));

	auto circle = entityManager.addEntity(EntityType::enemy);
	circle->cTransform = std::make_shared<CTransform>(CTransform({ 100, 20 }, { 0.1, 0.4 }));
	circle->cShape = std::make_shared<CShape>(CShape(50, { 255,0,0 }));

	auto circle2 = entityManager.addEntity(EntityType::enemy);
	circle2->cTransform = std::make_shared<CTransform>(CTransform({ 100, 200 }, { -0.1, 0.4 }));
	circle2->cShape = std::make_shared<CShape>(CShape(23, { 255,0,0 }));

	window.addCallback([&]()
		{
			entityManager.update();

			sMovement();
			sUserInput();
			sRender();

			m_currentFrame++;
		});
}

void Engine::run()
{
	window.open();

	m_running = true;
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
		player->cTransform->velocity.y = -PLAYER_SPEED;
	}
	else if (keyboardState[SDL_SCANCODE_DOWN])
	{
		player->cTransform->velocity.y = PLAYER_SPEED;
	}
	else
	{
		player->cTransform->velocity.y = 0;
	}

	if (keyboardState[SDL_SCANCODE_LEFT]) {
		player->cTransform->velocity.x = -PLAYER_SPEED;
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		player->cTransform->velocity.x = PLAYER_SPEED;
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
