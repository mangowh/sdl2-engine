#ifndef ENGINE_H
#define ENGINE_H

#include "EntityManager.h"
#include "Window.h"

class Engine
{
	double m_currentFrame = 0;
	bool m_running = true;

	std::shared_ptr<Entity> player;

	Window window;
	EntityManager entityManager;

public:
	Engine();

	void init();
	void update();
	// todo rework
	void mainLoop();

	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();
};

#endif // !ENGINE_H
