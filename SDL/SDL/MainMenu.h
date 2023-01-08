#pragma once
#include <SDL.h>
#include "InputManager.h"
#include "Visualisation.h"
#include "StarScape.h"
#include "Entity.h"
#include <iostream>

class MainMenu
{
public:
	static MainMenu* Instance();
	~MainMenu();

	void Update();
	void Render();
	bool IsGameRunning();
	void Initialise();
	void StopGame();
	void Uninitialise();

	Entity* CheckCollisions();
	bool TestCollision(Entity* player, Entity* block);

	bool RunGameCheck = true;
private:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	static MainMenu* s_instance;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	int rgb[3];
	InputManager* inputManager;
	Visualisation* m_visualisation;
	StarScape* m_stars;

	Entity* m_button;
	Entity* m_startbutton;
	Entity* m_mousepos;
	int mouseX, mouseY;

	std::vector<Entity*> m_entities;

	bool RunMenu = true;



};
