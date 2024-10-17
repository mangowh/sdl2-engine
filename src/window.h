#ifndef WINDOW_H
#define WINDOW_H

#include "CShape.h"
#include "CTransform.h"

#include <iostream>
#include <vector>
#include <memory>
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

	void draw() const;

	int getWidth() const;
	int getHeight() const;

	void setFullscreen() const;

	void drawShape(std::shared_ptr<CTransform> transform, std::shared_ptr<CShape> shape) const;

	void drawCircle(int x, int y, int radius, SDL_Color color) const
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (int w = 0; w < radius * 2; w++)
		{
			for (int h = 0; h < radius * 2; h++)
			{
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				if ((dx * dx + dy * dy) <= (radius * radius))
				{
					SDL_RenderDrawPoint(renderer, x + dx, y + dy);
				}
			}
		}
	}

	void drawRect(int x, int y, int width, int height, SDL_Color color) const
	{
		SDL_Rect r;
		r.x = x;
		r.y = y;
		r.w = width;
		r.h = height;

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		SDL_RenderFillRect(renderer, &r);
	}



	// experimental
	void initGL();
	void renderGL() const;
};

#endif // WINDOW_H