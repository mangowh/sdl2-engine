#ifndef ENGINE_H
#define ENGINE_H

#include "EntityManager.h"
#include "Window.h"
#include "Random.h"

struct Config
{
	double playerSpeed{ 10 };
};

class Engine
{
	Config config;

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
	Engine(Config config = {});

	void init();
	void update();

	void run();
	void pause();

	void spawnPlayer();
	void spawnEnemy();
	void spawnProjectile(Vector2 direction);

	auto isRunning() { return paused; }
};

#endif // !ENGINE_H
