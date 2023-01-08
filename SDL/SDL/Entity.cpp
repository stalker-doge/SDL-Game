#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{

}

const char* Entity::GetName()
{
    return m_name;
}

void Entity::Initialise(const char* name, const char* imageName)
{
    m_name = name;
    m_imageName = imageName;
    m_Vis = Visualisation::Instance();
    imageID = m_Vis->AddImage(m_imageName);
    m_Rect = new SDL_Rect{ rand() % 1280,rand() % 720,64,64 };
    isEnabled = true;
	isDynamic = false;
    lifetime = 0;
}

void Entity::Render()
{
    if (imageID < 0)
    {
		isEnabled = false;
    }
    if (isEnabled)
    {
        m_Vis->DrawImage(imageID, m_Rect);
    }

}

void Entity::SetStatus(bool enabling)
{
    lifetime = maxlifetime;
    isEnabled = enabling;
}

bool Entity::GetStatus()
{
    return isEnabled;
}

bool Entity::GetDyanmic()
{
    return isDynamic;
}

void Entity::Update()
{
}

void Entity::SetLifetime(float lf)
{
	maxlifetime = lf;
	lifetime = lf;
}

float Entity::GetMaxLifetime()
{
    return maxlifetime;
}

void Entity::GenericAction()
{
}

float Entity::GetLifetime()
{
    return lifetime;
}

int Entity::OnCollision(Entity* collider)
{
    return 0;
}

SDL_Rect* Entity::GetLocation()
{
    return m_Rect;
}

void Entity::SetPosition(int x, int y)
{
	m_Rect->x = x;
	m_Rect->y = y;
}

void Entity::ChangeLocation(int x, int y, int h, int w)
{
	m_Rect->x = x;
	m_Rect->y = y;
	m_Rect->h = h;
	m_Rect->w = w;
}

void Entity::SetName(const char* name)
{
    m_name=name;
}
