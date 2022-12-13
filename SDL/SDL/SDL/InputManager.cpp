#include "InputManager.h"

void InputManager::Update()
{
    SDL_PollEvent(gameEvent);
    switch (gameEvent->type)
    {
        case SDL_KEYUP:
        {
            m_keys[SDL_GetScancodeFromKey(gameEvent->key.keysym.sym)] = 0;
            break;
        }
        case SDL_KEYDOWN:
        {
            m_keys[SDL_GetScancodeFromKey(gameEvent->key.keysym.sym)] = 1;
            break;
        }

    }
}

bool InputManager::GetKeyUp(SDL_Keycode userKey)
{
    if (gameEvent->key.keysym.sym == userKey)
    {
        return true;
    }
    return false;
}

bool InputManager::GetKeyDown(SDL_Keycode userKey)
{
    if (gameEvent->key.keysym.sym == userKey)
    {
        return true;
    }
    return false;
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
