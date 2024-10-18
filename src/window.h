#ifndef WINDOW_H
#define WINDOW_H

#include "CShape.h"
#include "CTransform.h"
#include "Entity.h"

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window
{
	bool shouldQuit = false;

	/* Window title */
	const std::string windowTitle = "test";
	/* Screen width */
	const int screenWidth = 1920;
	/* Screen height */
	const int screenHeight = 1080;
	/* The window object to render to */
	SDL_Window* window = NULL;
	/* The surface contained by the window */
	SDL_Surface* surface = NULL;
	SDL_Renderer* renderer = NULL;
	/* Event handler */
	SDL_Event pollEvent();
	std::vector<std::function<void(void)>> frameCallbacks = {};

	void mainLoop();

public:
	Window();
	~Window();

	const Uint8* keyboardState;

	void init();
	void open();
	void addCallback(std::function<void(void)> func);
	void update() const;
	void clear() const;
	void close();

	void render() const;

	int getWidth() const;
	int getHeight() const;

	void setFullscreen() const;

	// callbacks
	std::function<void(Vector2)> onClick = NULL;

	// drawing
	void drawShape(std::shared_ptr<CTransform> transform, std::shared_ptr<CShape> shape) const;
	void drawPoint(int x, int y, SDL_Color color) const;
	void drawRect(int x, int y, int width, int height, SDL_Color color) const;
	void drawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, SDL_Color color) const;
	void drawCircle(Vector2 center, float radius, SDL_Color color, int numSegments) const;

	void drawDebug(std::shared_ptr<Entity> e) const;

	// experimental
	void initGL();
	void renderGL() const;
};

#endif // WINDOW_H