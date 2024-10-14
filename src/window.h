#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <functional>

class Window {

	/* Window title */
	const std::string windowTitle = "test";

	/* Screen width */
	const int screenWidth = 640;

	/* Screen height */
	const int screenHeight = 480;

	/* The window object to render to */
	SDL_Window* gWindow = NULL;

	/* The surface contained by the window */
	SDL_Surface* gScreenSurface = NULL;

	SDL_Renderer* renderer = NULL;

	/* Event handler */
	SDL_Event e;

	std::vector<std::function<void(void)>> updateCallbacks = {};
	std::vector<std::function<void(SDL_Renderer*)>> renderCallbacks = {};

	bool mainLoop();

public:
	Window();
	~Window();

	void init();
	void initGL();

	void open();

	void addUpdateCallback(std::function<void(void)> func);
	void addRenderCallback(std::function<void(SDL_Renderer*)> func);

	void update() const;
	void render() const;
	void renderGL() const;

	void close();
};

#endif