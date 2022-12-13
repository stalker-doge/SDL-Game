#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
public:
	Enemy();
	~Enemy();
	const char* GetName();
	void Initialise();
	void Update();
	void OnCollision(Entity* collider) override;
private:
	int imageID;
	int enemyX, enemyY;
	float enemySpeed;
};

