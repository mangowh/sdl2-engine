#include "Engine.h"

const int PLAYER_SPEED = 3;


Engine::Engine()
{
	init();
}

void Engine::init()
{
	player = entityManager.addEntity(EntityType::player);
	player->cTransform = std::make_shared<CTransform>(CTransform({ (window.getWidth() - 100) / 2.0f, (window.getHeight() - 100) / 2.0f }, { 100, 100 }));
	player->cShape = std::make_shared<CShape>(CShape(100, 100, { 255,100,0 }));

	window.addCallback([&]()
		{
			entityManager.update();

			sUserInput();

			if (!paused)
			{
				sMovement();
				sCollision();
			}

			sRender();

			currentFrame++;
		});

	window.open();
}

void Engine::run()
{
	paused = false;
}

void Engine::pause()
{
	paused = true;
}

void Engine::spawnEnemy()
{
	Random rand;

	const int dimension = rand.genRandomInt(25, 75);

	auto enemy = entityManager.addEntity(EntityType::enemy);
	enemy->cTransform = std::make_shared<CTransform>(CTransform(
		{ (float)rand.genRandomInt(0, window.getWidth() - dimension), (float)rand.genRandomInt(0, window.getHeight() - dimension) },
		{ (float)dimension, (float)dimension },
		{ rand.genRandomInt(1, 100) / 10.0f, rand.genRandomInt(1, 100) / 10.0f }));

	enemy->cShape = std::make_shared<CShape>(CShape(50, { (uint8_t)rand.genRandomInt(0, 255), (uint8_t)rand.genRandomInt(0, 255), (uint8_t)rand.genRandomInt(0, 255) }));
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

void Engine::sCollision()
{
	for (auto& e : entityManager.getEntities())
	{
		if (e->cTransform) {
			const int windowW = window.getWidth();
			const int windowH = window.getHeight();

			// Screen collision
			if (e->cTransform->pos.x < 0) {
				e->cTransform->pos.x = 0;
			}

			if (e->cTransform->pos.x + e->cTransform->dimension.x > windowW) {
				e->cTransform->pos.x = windowW - e->cTransform->dimension.x;
			}


			if (e->cTransform->pos.y < 0) {
				e->cTransform->pos.y = 0;
			}

			if (e->cTransform->pos.y + e->cTransform->dimension.x > windowH) {
				e->cTransform->pos.y = windowH - e->cTransform->dimension.x;
			}
		}
	}
}


void Engine::sUserInput()
{
	// TODO remove SDL references in Engine

	auto keyboardState = window.keyboardState;

	// Player movement
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

	// Pause
	// TODO use SDL_Event pool for 
	if (keyboardState[SDL_SCANCODE_P]) {
		if (!paused)
		{
			pause();
		}
		else
		{
			run();
		}
	}

	// Fullscreen
	// TODO use SDL_Event pool for 
	if (keyboardState[SDL_SCANCODE_F]) {
		window.setFullscreen();
	}

	if (keyboardState[SDL_SCANCODE_E]) {
		spawnEnemy();
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

