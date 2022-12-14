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
	void OnCollision(Entity* collider) override;
	void Shoot(SDL_Rect* location);
private:
	int imageID;
	int bulletX, bulletY;
	float bulletSpeed;
};

