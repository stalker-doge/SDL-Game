#pragma once
#include "Entity.h"
class Bullet :
    public Entity
{
public:
	Bullet();
	~Bullet();
	const char* GetName();
	void Initialise();
	void Update();
	int OnCollision(Entity* collider) override;
	void Shoot(SDL_Rect* location);
	void SetSpeed(float speed);
private:
	int imageID;
	int bulletX, bulletY;
	float bulletSpeed;
};

