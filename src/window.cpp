#include "window.h"

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;  // Frame delay in milliseconds

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
		window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
	}
}

void Window::open()
{
	while (!shouldQuit)
	{
		mainLoop();
	}
}

void Window::mainLoop()
{
	Uint32 frameStart = SDL_GetTicks();  // Start time for frame

	//Handle events on queue
	auto event = pollEvent();

	//User requests quit
	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
	{
		shouldQuit = true;
	}

	// Get the keyboard state
	keyboardState = SDL_GetKeyboardState(NULL);

	update();

	// Calculate frame time and delay to maintain fixed FPS
	Uint32 frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < FRAME_DELAY) {
		SDL_Delay(FRAME_DELAY - frameTime); // Delay the remaining time to maintain FPS
	}
}

SDL_Event Window::pollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		return event;
	}
}


void Window::addCallback(std::function<void(void)> func)
{
	// TODO prevent adding while iterating
	frameCallbacks.push_back(func);
}

void Window::update() const
{
	for (auto& func : frameCallbacks) {
		func();
	}
}

void Window::clear() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 25, 255);
	SDL_RenderClear(renderer);
}

void Window::close()
{
	//Destroy window
	if (window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}

void Window::draw() const
{
	SDL_RenderPresent(renderer);
}

void Window::drawShape(std::shared_ptr<CTransform> transform, std::shared_ptr<CShape> shape) const
{
	SDL_Color color = { .r = shape->color.r, .g = shape->color.g, .b = shape->color.b , .a = shape->color.a };

	if (shape->type == circle) {
		drawCircle(transform->pos.x, transform->pos.y, shape->radius, color);
	}
	else
	{
		drawRect(transform->pos.x, transform->pos.y, shape->width, shape->height, color);
	}
}



// experimental
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

	SDL_GL_SwapWindow(window);
}