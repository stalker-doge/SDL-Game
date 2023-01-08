#pragma once
#include <SDL.h>
#include "InputManager.h"
#include "Visualisation.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "EnemySpawner.h"
#include "StarScape.h"
#include "Boss.h"
#include <iostream>
#include <SDL_ttf.h>
#include "UserInterface.h"
#include "MainMenu.h"
class Game
{
public:
	static Game* Instance();
	~Game();
	void Update();
	void Render();
	bool IsGameRunning();
	void Initialise();
	void Uninitialise();
	void StopGame();
	void RestartGame();
	Entity* CheckCollisions();
	bool TestCollision(Entity* player, Entity* block);
	SDL_Renderer* GetRenderer();
private:
	Game();
	Game(const Game&) = delete;
	static Game* s_instance;
	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	int rgb[3];
	InputManager* inputManager;
	Visualisation* m_visualisation;
	bool running;
	Player* m_player;
	Enemy* m_enemy;
	Bullet* m_bullet;
	std::vector<Entity*> m_entities;
	ObjectPool* m_bulletPool;
	StarScape* m_starScape;
	EnemySpawner* m_enemySpawner;
	Boss* m_boss;
	Uint64 timer,shootTimer;
	UserInterface* m_userInterface;
	int score;
	MainMenu* m_mainMenu;
};

