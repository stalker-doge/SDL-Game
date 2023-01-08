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
	auto debug = imageID;
    Entity::isEnabled = true;
    Entity::isDynamic = true;
    Entity::imageID = imageID;
	m_name = "enemy";
    m_Rect = new SDL_Rect{ 300,300,64,64 };
    enemySpeed = 1;
	enemyHP = 5;
	score = 10;
}

void Enemy::Update()
{
	if (enemyHP < 0)
	{
		Entity::isEnabled = false;
	}
    m_Rect->x -= enemySpeed;
}

int Enemy::OnCollision(Entity* collider)
{
	if (collider->GetName() == "bullet")
	{
		collider->SetStatus(false);
		enemyHP -= 1;
		if (enemyHP <= 0)
		{
			return score;
		}
	}
	return 0;
	
}

int Enemy::GetHP()
{
	return enemyHP;
}

void Enemy::EnemyUpgrade()
{
	imageID = m_Vis->AddImage("enemy2.bmp");
	Entity::imageID = imageID;
	m_name = "enemy";
	enemySpeed = 2;
	enemyHP = 10;
	score = 20;
}
