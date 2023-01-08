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
	virtual int OnCollision(Entity* collider) override;
	virtual int GetHP();
	virtual void EnemyUpgrade();
private:
	int imageID;
	int enemyX, enemyY;
	float enemySpeed;
	int enemyHP;
	int score;
};

