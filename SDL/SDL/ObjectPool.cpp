#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
}

ObjectPool::~ObjectPool()
{
	m_Pool.clear();
	m_inUse.clear();
}

void ObjectPool::Update()
{
	for (int i = 0; i < m_inUse.size(); i++)
	{
		if (m_inUse[i]->GetLifetime() == 0)
		{
			ReUseObject(m_inUse[i]);
		}
		else
		{
			m_inUse[i]->Update();
		}
	}
}

Bullet* ObjectPool::GetObject()
{
	if (m_Pool.size() == 0)
	{
		return CreateObject();
	}
	else
	{
		Bullet* object = m_Pool.back();
		m_Pool.pop_back();
   		m_inUse.push_back(object);
		return object;
	}
}

Bullet* ObjectPool::CreateObject()
{
	Bullet* temp = new Bullet();
	temp->Initialise();
	m_inUse.push_back(temp);
	return temp;
}

void ObjectPool::ReUseObject(Bullet* object)
{
	for (int i = 0; i < m_inUse.size(); i++)
	{
		if (m_inUse[i] == object)
		{
			m_inUse.erase(m_inUse.begin() + i);
			break;
		}
	}
	object->SetLifetime(object->GetMaxLifetime());
	m_Pool.push_back(object);
}

void ObjectPool::Initialise(int size)
{
	max_size = size;
	for (int i = 0; i < max_size; i++)
	{
		m_Pool.push_back(CreateObject());
	}
}

void ObjectPool::Shoot(SDL_Rect* location)
{
	Bullet* temp = GetObject();
	temp->Shoot(location);
}

void ObjectPool::Render()
{
	for (int i = 0; i < m_inUse.size(); i++)
	{
		m_inUse[i]->Render();
	}
}

std::vector<Bullet*> ObjectPool::GetUsedVector()
{
	return m_inUse;
}
