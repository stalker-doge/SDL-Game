#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::Update()
{
    for (int i = 0; i < m_inUse.size(); i++)
    {
        if (m_inUse[i]->GetLifetime() <= 0)
        {
            m_inUse[i]->SetStatus(false);
            m_Pool.push_back(m_inUse[i]);
            m_inUse.erase(m_inUse.begin()+i);
        }
        else
        {
            m_inUse[i]->Update();
        }
    }
}

Bullet* ObjectPool::GetObject()
{
    if (m_inUse.empty())
    {
        m_inUse.push_back(m_Pool.front());
        m_Pool.erase(m_Pool.begin());
        return m_inUse.front();
    }
    else if (m_Pool.empty())
    {
        for (int i = 0; i < m_inUse.size(); i++)
        {
            if (m_inUse[i]->GetLifetime() == 0)
            {
                m_inUse[i]->SetStatus(true);
                m_Pool.push_back(m_inUse[i]);
            }
        }
    }
    else
    {
        CreateObject();
        return m_inUse.back();
    }
}

Bullet* ObjectPool::CreateObject()
{
    Bullet* temp = new Bullet();
    temp->Initialise();
    m_inUse.push_back(temp);
    return m_inUse.front();
}

void ObjectPool::ReUseObject(Bullet* object)
{
    for (int i = 0; i < m_Pool.size(); i++)
    {
        if (m_Pool[i] = object)
        {
            object->SetStatus(true);
            m_inUse.push_back(object);
        }
    }
}

void ObjectPool::Initialise(Bullet* poolCreator)
{
    m_Pool.push_back(poolCreator);
}
