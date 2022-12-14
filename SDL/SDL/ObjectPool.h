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
	void Initialise(Bullet* poolCreator);
private:
	Bullet* ObjectType;
	std::vector<Bullet*> m_Pool;
	std::vector<Bullet*> m_inUse;
};

