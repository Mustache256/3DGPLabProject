#include "Movement.h"


Movement::Movement()
{
	//Set movemnt check and quit check values to correct values by default
	m_movementCheck = 0;
	m_quitCheck = false;
}

int Movement::Move()
{
	//Create event manager to manage player input
	SDL_Event event = { 0 };

	//While loop that ensures program continually checks for player input
	while (SDL_PollEvent(&event))
	{
		//Switch statement that determines what to do based off of player input
		switch (event.type)
		{
		//Case for key press
		case SDL_KEYDOWN:
			//Switch statement that determine what to do depending on which key the player pressed
			switch (event.key.keysym.sym)
			{
			//Case for moving the player left
			case SDLK_a:
				std::cout << "Left key pressed" << std::endl;
				m_movementCheck = 1;
				break;
			//Case for moving the player right
			case SDLK_d:
				std::cout << "Right key pressed" << std::endl;
				m_movementCheck = 2;
				break;
			//Case for moving the player up
			case SDLK_w:
				std::cout << "Up key pressed" << std::endl;
				m_movementCheck = 3;
				break;
			//Case for moving the player down
			case SDLK_s:
				std::cout << "Down key pressed" << std::endl;
				m_movementCheck = 4;
				break;
			//Case for exiting the game
			case SDLK_ESCAPE:
				std::cout << "Game Quit" << std::endl;
				m_quitCheck = true;
				break;
			}
			break;
		//Case for key release
		case SDL_KEYUP:
			//Switch statement that determine what to do depending on which key the player released
			switch (event.key.keysym.sym)
			{
			//Case for stopping the player from moving left
			case SDLK_a:
				std::cout << "Left key released" << std::endl;
				m_movementCheck = 0;
				break;
			//Case for stopping the player from moving right
			case SDLK_d:
				std::cout << "Right key released" << std::endl;
				m_movementCheck = 0;
				break;
			//Case for stopping the player from moving up
			case SDLK_w:
				std::cout << "Up key released" << std::endl;
				m_movementCheck = 0;
				break;
			//Case for stopping the player from moving down
			case SDLK_s:
				std::cout << "Down key released" << std::endl;
				m_movementCheck = 0;
				break;
			}
			break;
		default:
			break;
		}
	}
	//Return movement check result
	return m_movementCheck;
}