#pragma once
#include <SDL.h>
class Game
{
public:
	void Update();
	void Render();
	bool IsGameRunning();
	void Initialise();
	void Uninitialise();
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
};

