#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
public:
	Boss();
	~Boss();
	const char* GetName() override;
	void Initialise() override;
	void Update() override;
	int OnCollision(Entity* collider) override;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor,SDL_Renderer* render);
	void Render();
	bool bossDeath1, bossDeath2;
private:
	int imageID;
	int bossX, bossY;
	float bossSpeed;
	int bossHP = 1000;
	int maxHP;
};

