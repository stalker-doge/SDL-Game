#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

const char* Bullet::GetName()
{
	return "bullet";
}

void Bullet::Initialise()
{
	m_Vis = Visualisation::Instance();
	imageID = m_Vis->AddImage("bullet.bmp");
	Entity::isEnabled = false;
	Entity::isDynamic = true;
	Entity::imageID = imageID;
	bulletSpeed = 10;
	lifetime = 100;
	maxlifetime = 100;
	m_Rect = new SDL_Rect{ 0,0,64,64 };
}

void Bullet::Update()
{
	if (isEnabled)
	{
		m_Rect->x += bulletSpeed;
		lifetime--;
	}

}

void Bullet::OnCollision(Entity* collider)
{
}

void Bullet::Shoot(SDL_Rect* location)
{
	m_Rect->x = location->x;
	m_Rect->y = location->y;
	isEnabled = true;
}
