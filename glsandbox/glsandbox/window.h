
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <stdexcept>

class Window {
public:
	Window();
	~Window();
	void Swap();
private:
	SDL_Window* window; 
};