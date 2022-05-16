#define SDL_MAIN_HANDLED
#include "Application.h"

int main()
{
	std::unique_ptr<Application> game = std::make_unique<Application>();
	game->update();
	return 0;
}