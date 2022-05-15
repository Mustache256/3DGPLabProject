#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Movement
{
public:
	Movement();
	~Movement();

	int Move();
	bool GetQuit() { return m_quit; }

private:
	int m_moveCheck;
	bool m_quit;
};

