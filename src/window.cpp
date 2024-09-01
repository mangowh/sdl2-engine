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
	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

		}
		else {

			gContext = SDL_GL_CreateContext(gWindow);

			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				initGL();
			}
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
	}

	update();
	render();
}

void Window::update() const
{

}

void Window::render() const
{
	// EXAMPLE CUBE
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(0.4f, 0.0f, 1.0f, 0.0f);    // Rotate The cube around the Y axis
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
	//Deallocate surface
	if (gXOut) {
		SDL_FreeSurface(gXOut);
		gXOut = NULL;
	}

	//Destroy window
	if (gWindow) {
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}
