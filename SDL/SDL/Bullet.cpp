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
	Entity::isEnabled = true;
	Entity::isDynamic = true;
	Entity::imageID = imageID;
	bulletSpeed = 1;
}

void Bullet::Update()
{
	m_Rect->x += bulletSpeed;
}

void Bullet::OnCollision(Entity* collider)
{
}
