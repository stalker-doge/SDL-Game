#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

const char* Enemy::GetName()
{
	return "enemy";
}

void Enemy::Initialise()
{
    m_Vis = Visualisation::Instance();
    imageID = m_Vis->AddImage("enemy.bmp");
    Entity::isEnabled = true;
    Entity::isDynamic = true;
    Entity::imageID = imageID;
	m_name = "enemy";
    m_Rect = new SDL_Rect{ 300,300,64,64 };
    enemySpeed = 1;
}

void Enemy::Update()
{
    m_Rect->x -= enemySpeed;
}

void Enemy::OnCollision(Entity* collider)
{
	if (collider->GetName() == "player")
	{
		collider->SetStatus(false);
	}
	else if (collider->GetName() == "bullet")
	{
		collider->SetStatus(false);
		this->SetStatus(false);
	}
	
}
