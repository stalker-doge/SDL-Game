#pragma once
#include <SDL.h>
#include "InputManager.h"
#include "Visualisation.h"

class MainMenu
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
	int rgb[3];
	InputManager* inputManager;
	Visualisation* m_visualisation;


};

