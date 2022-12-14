#pragma once
#include <SDL.h>
#include "InputManager.h"
#include "Visualisation.h"
#include "Entity.h"

class MainMenu
{
public:
	static MainMenu* Instance();
	~MainMenu();

	void Update();
	void Render();
	bool IsGameRunning();
	void Initialise();
	void Uninitialise();
private:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	static MainMenu* s_instance;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	int rgb[3];
	InputManager* inputManager;
	Visualisation* m_visualisation;

	Entity* Button;

	bool RunGame = true;
};

