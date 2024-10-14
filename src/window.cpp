#include "window.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>

Window::Window()
{
	init();
}

Window::~Window()
{
	close();
}

void Window::init()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
		}
	}
}

void Window::initGL()
{
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		throw "Cannot initialize Projection Matrix";
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		throw "Cannot initialize Modelview Matrix";

	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		throw "Cannot initialize clear color";
	}
}

void Window::open()
{
	while (!mainLoop()) {}
}

bool Window::mainLoop()
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return true;
		}

		update();
		render();
	}
}

void Window::addUpdateCallback(std::function<void(void)> func)
{
	updateCallbacks.push_back(func);
}

void Window::addRenderCallback(std::function<void(SDL_Renderer*)> func)
{
	renderCallbacks.push_back(func);
}

void Window::update() const
{
	for (auto& func : updateCallbacks) {
		func();
	}
}

void Window::render() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (auto& func : renderCallbacks) {
		func(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Window::renderGL() const
{
	// EXAMPLE CUBE
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(0.4f, 0.0f, 1.0f, 2.0f);    // Rotate The cube around the Y axis
	glRotatef(0.2f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	// ! END EXAMPLE CUBE

	SDL_GL_SwapWindow(gWindow);
}

void Window::close()
{
	//Destroy window
	if (gWindow) {
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}
