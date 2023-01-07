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
	Entity* m_block[3];
	Entity* m_spikeBlocks[5];
	Entity* m_star;
	Enemy* m_enemy;
	Bullet* m_bullet;
	std::vector<Entity*> m_entities;
	ObjectPool* m_bulletPool;
	StarScape* m_starScape;
	EnemySpawner* m_enemySpawner;

};

