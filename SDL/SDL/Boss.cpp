#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

const char* Boss::GetName()
{
	return "boss";
}

void Boss::Initialise()
{
	m_Vis = Visualisation::Instance();
	imageID = m_Vis->AddImage("enemy.bmp");
	Entity::isEnabled = true;
	Entity::isDynamic = true;
	Entity::imageID = imageID;
	m_name = "boss";
	m_Rect = new SDL_Rect{ 300,300,200,200 };
	bossSpeed = 1;
}

void Boss::Update()
{
	m_Rect->x -= bossSpeed;
}

void Boss::OnCollision(Entity* collider)
{
}

void Boss::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* render)
{
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(render, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(render, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(render, &bgrect);
	SDL_SetRenderDrawColor(render, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	int pw = (int)((float)w * Percent);
	int px = x + (w - pw);
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(render, &fgrect);
	SDL_SetRenderDrawColor(render, old.r, old.g, old.b, old.a);
}
