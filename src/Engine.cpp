#include "Engine.h"

Engine::Engine()
{
	auto circle = entityManager.addEntity("circle");
	circle->cTransform = std::make_shared<CTransform>(CTransform({ 100, 20 }, { 0.001, 0.004 }));
	circle->cShape = std::make_shared<CShape>();
	//circle->cShape->type = "rect";

	window.addCallback([&]()
		{
			entityManager.update();

			sMovement();
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
	auto entities = entityManager.getEntities();
	for (auto& e : entities)
	{
		if (e->cTransform) {
			e->cTransform->pos.x += e->cTransform->velocity.x;
			e->cTransform->pos.y += e->cTransform->velocity.y;
		}
	}
}

void Engine::sRender()
{
	auto entities = entityManager.getEntities();
	for (auto& e : entities) {
		window.clear();

		if (e->cTransform && e->cShape)
		{
			window.drawShape(e->cTransform, e->cShape);
		}

		window.draw();
	}
}
