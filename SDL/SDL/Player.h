#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
	Player();
	~Player();
	const char* GetName();
	void Initialise();
	void Update();
	void OnCollision(Entity* collider) override;
private:
	int imageID;
	int playerX, playerY;
	float playerSpeed;
	InputManager* playerInput;
};

