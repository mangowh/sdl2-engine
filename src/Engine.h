#ifndef ENGINE_H
#define ENGINE_H

#include "EntityManager.h"
#include "Window.h"
#include "Random.h"

class Engine
{
	Window window;
	EntityManager entityManager;

	// systems
	void sMovement();
	void sCollision();
	void sUserInput();
	void sLifespan();
	void sEnemySpawner();
	void sRender();

	//font & text

	std::shared_ptr<Entity> player;

	int currentFrame = 0;

	bool paused = false;

	// various configurations

public:
	Engine();

	void init();
	void update();

	void run();
	void pause();

	void spawnEnemy();
	void spawnProjectile(Vector2 direction);

	auto isRunning() { return paused; }
};

#endif // !ENGINE_H
