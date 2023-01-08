#pragma once
#include <SDL.h>
#include "Enemy.h"
#include <vector>
class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();
	void SpawnEnemy();
	void Update();
	void Render();
	void Initialise();
	void CleanUp();
	void Upgrade(bool upgrade);
	std::vector<Enemy*> GetEnemyVector();
private:
	SDL_Rect* m_Rect;
	SDL_Rect* m_SpawnRect;
	int enemyCount = 0;
	int spawnCount = 0;
	int spawnRate = 5;
	int maxEnemies = 10;
	int spawnX, spawnY;
	int spawnWidth, spawnHeight;
	int spawnTimer = 0;
	int spawnDelay = 5;
	bool spawn = false;
	bool spawnOnce = true;
	Enemy* enemy;
	std::vector<Enemy*> m_enemies;
	bool canUpgrade = false;
};

