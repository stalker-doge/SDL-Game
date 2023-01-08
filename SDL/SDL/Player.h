#pragma once
#include "Entity.h"
#include "Bullet.h"
class Player : public Entity
{
public:
	Player();
	~Player();
	const char* GetName();
	void Initialise();
	void Update();
	int OnCollision(Entity* collider) override;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* render);
	void Render();
	int GetHP();
private:
	int imageID;
	int playerX, playerY;
	float playerSpeed;
	InputManager* playerInput;
	int HP;
};

