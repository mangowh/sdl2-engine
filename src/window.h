#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <iostream>

class Window {
	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;
	//The image we will load and show on the screen
	SDL_Surface* gXOut = NULL;
	//OpenGL context
	SDL_GLContext gContext;

	//Event handler
	SDL_Event e;

public:
	Window();
	~Window();

	void init();
	void initGL();

	bool mainLoop();

	void update() const;
	void render() const;

	void close();
};

#endif 