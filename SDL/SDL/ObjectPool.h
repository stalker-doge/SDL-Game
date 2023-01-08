#pragma once
#include <SDL.h>
#include <vector>
#include "Bullet.h"
class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	void Update();
	Bullet* GetObject();
	Bullet* CreateObject();
	void ReUseObject(Bullet* object);
	void Initialise(int max_size);
	void Shoot(SDL_Rect* location);
	void EnemyShoot(SDL_Rect* location);
	void Render();
	void Wipe();
	std::vector<Bullet*> GetUsedVector();
private:
	int max_size;
	std::vector<Bullet*> m_Pool;
	std::vector<Bullet*> m_inUse;
};

