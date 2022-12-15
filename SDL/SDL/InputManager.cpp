#include "InputManager.h"
#include <iostream>


InputManager::~InputManager()
{
    s_instance = nullptr;
}

InputManager* InputManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new InputManager();
        return s_instance;
    }
    return s_instance;
}

void InputManager::Update()
{
    SDL_Event gameEvent;
    m_keyDOWN.clear();
    m_keyUP.clear();
    while (SDL_PollEvent(&gameEvent))
    {
        switch (gameEvent.type)
        {
            case SDL_KEYUP:
            {
                m_keys[SDL_GetScancodeFromKey(gameEvent.key.keysym.sym)] = 0;
                m_keyUP.push_back(gameEvent.key.keysym.sym);
                break;
            }
            case SDL_KEYDOWN:
            {
                 m_keys[SDL_GetScancodeFromKey(gameEvent.key.keysym.sym)] = 1;
                 m_keyDOWN.push_back(gameEvent.key.keysym.sym);

                break;
            }
            case SDL_MOUSEMOTION:
            {
                int x, y;

                SDL_GetMouseState(&x, &y);

                std::cout << x << " : " << y << std::endl;
            }
        }
    }
}

bool InputManager::GetKeyUp(SDL_Keycode userKey)
{
    return (std::find(m_keyUP.begin(), m_keyUP.end(), userKey) != m_keyUP.end());
}

bool InputManager::GetKeyDown(SDL_Keycode userKey)
{
    return std::find(m_keyDOWN.begin(), m_keyDOWN.end(), userKey) != m_keyDOWN.end();
}

bool InputManager::GetKeyHeld(SDL_Keycode userKey)
{
    if (m_keys[SDL_GetScancodeFromKey(userKey)] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InputManager::Destroy()
{
    s_instance = nullptr;
}

InputManager::InputManager()
{
}

InputManager* InputManager::s_instance = nullptr;