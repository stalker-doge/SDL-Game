#include "EnemySpawner.h"

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::SpawnEnemy()
{
	if (spawn)
	{
		if (spawnOnce)
		{
			spawnX = rand() % m_SpawnRect->w + m_SpawnRect->x;
			spawnY = rand() % m_SpawnRect->h + m_SpawnRect->y;
			spawnOnce = false;
		}
		if (spawnTimer < spawnDelay)
		{
			spawnTimer++;
		}
		else
		{
			spawnTimer = 0;
			spawnOnce = true;
			enemy = new Enemy();
			enemy->Initialise();
			if (canUpgrade)
			{
				enemy->EnemyUpgrade();
			}
			enemy->SetPosition(spawnX, spawnY);
			enemyCount++;
			m_enemies.push_back(enemy);
			spawn = false;
		}
	}
	else
	{
		if (spawnCount < spawnRate)
		{
			spawnCount++;
		}
		else
		{
			spawnCount = 0;
			spawn = true;
		}
	}
}

void EnemySpawner::Update()
{
	SpawnEnemy();
	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->GetStatus())
		{
			m_enemies[i]->Update();
		}
	}
	CleanUp();
}

void EnemySpawner::Render()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
		if (m_enemies[i]->GetHP() <= 0)
		{
			m_enemies.erase(m_enemies.begin() + i);
		}
	}
}

void EnemySpawner::Initialise()
{
	m_Rect = new SDL_Rect{ rand() % 980+300,rand() % 420+300,64,64 };
	m_SpawnRect = new SDL_Rect{ 0,0,1280,720 };
}

void EnemySpawner::CleanUp()
{
	//erases enemies that aren't active anymore
	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (!m_enemies[i]->GetStatus())
		{
			m_enemies.erase(m_enemies.begin() + i);
		}
	}
}

void EnemySpawner::Upgrade(bool upgrade)
{
	canUpgrade = upgrade;
}

std::vector<Enemy*> EnemySpawner::GetEnemyVector()
{
	return m_enemies;
}
