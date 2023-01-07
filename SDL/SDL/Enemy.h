#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
public:
	Enemy();
	~Enemy();
	virtual const char* GetName();
	virtual void Initialise();
	virtual void Update();
	virtual void OnCollision(Entity* collider) override;
private:
	int imageID;
	int enemyX, enemyY;
	float enemySpeed;
};

