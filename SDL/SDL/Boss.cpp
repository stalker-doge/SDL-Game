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
	Entity::isEnabled = false;
	Entity::isDynamic = true;
	Entity::imageID = imageID;
	m_name = "boss";
	m_Rect = new SDL_Rect{ 300,300,200,200 };
	bossSpeed = 1;
	bossDeath1 = false;
	bossDeath2 = false;
	maxHP = bossHP;
}

void Boss::Update()
{
	if (bossHP <= 0)
	{
		isEnabled = false;
	}
	if (isEnabled)
	{
		if (m_Rect->y < 0)
		{
			bossSpeed = 1;
		}
		if (m_Rect->y + m_Rect->h > 720)
		{
			bossSpeed = -1;
		}
		m_Rect->y += bossSpeed;
	}
}

int Boss::OnCollision(Entity* collider)
{
	if (collider->GetName() == "bullet")
	{
		bossHP -= 1;
		if (bossHP <= 0)
		{
			if (bossDeath1)
			{
				bossDeath2 = true;
				return 1000;
			}
			else
			{
				bossDeath1 = true;
				return 1000;
			}
		}
		return 0;
		collider->SetStatus(false);
	}
	return 0;
}

void Boss::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* render)
{
	SDL_Rect background;
	background.x = x;
	background.y = y;
	background.w = w;
	background.h = h;
	SDL_SetRenderDrawColor(render, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(render, &background);

	SDL_Rect foreground;
	foreground.x = x;
	foreground.y = y;
	foreground.w = (int)(w * Percent);
	foreground.h = h;
	SDL_SetRenderDrawColor(render, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	SDL_RenderFillRect(render, &foreground);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

void Boss::Render()
{
	if (isEnabled)
	{
		m_Vis = Visualisation::Instance();
		SDL_Color FGColor = { 0, 255, 0, 255 };
		SDL_Color BGColor = { 255, 0, 0, 255 };
		m_Vis->DrawImage(imageID, m_Rect);
		RenderHPBar(m_Rect->x, m_Rect->y - 10, m_Rect->w, 5, (float)bossHP / maxHP, FGColor, BGColor, m_Vis->GetRender());
	}
}
