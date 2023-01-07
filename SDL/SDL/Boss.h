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
	void OnCollision(Entity* collider) override;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor,SDL_Renderer* render);
private:
	int imageID;
	int bossX, bossY;
	float bossSpeed;
};

