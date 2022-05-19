#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Movement
{
public:
	//Movemnt constructor and destructor
	Movement();
	~Movement();

	//Function that handles movemnt management
	int Move();
	//Get quit manager boolean value
	bool GetQuit() { return m_quitCheck; }

private:
	//Movement check manager variable
	int m_movementCheck;
	//Quit check maanger variable
	bool m_quitCheck;
};

