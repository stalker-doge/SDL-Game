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

	Entity* CheckCollisions();
	bool TestCollision(Entity* player, Entity* block);
private:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	static MainMenu* s_instance;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	int rgb[3];
	InputManager* inputManager;
	Visualisation* m_visualisation;

	Entity* m_button;

	Entity* m_mousepos;

	std::vector<Entity*> m_entities;

	bool RunGame = true;

};

