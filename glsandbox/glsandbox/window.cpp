#include "window.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <stdexcept>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Window::Window()
{
	window = SDL_CreateWindow("My Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::Swap()
{
	SDL_GL_SwapWindow(window);
}