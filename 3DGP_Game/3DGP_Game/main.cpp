#define SDL_MAIN_HANDLED
#include "Application.h"

int main()
{
	//Create new application object and call main update function for the program 
	std::unique_ptr<Application> game = std::make_unique<Application>();
	game->update();
	//output you died message to console and wait for player input to close the game
	std::cout << "YOU DIED! Press any key to close the game!" << std::endl;
	std::cin.get();
	return 0;
}