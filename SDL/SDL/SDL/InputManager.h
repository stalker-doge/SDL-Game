#pragma once
#include <SDL.h>
class InputManager
{
public:
	void Update();
	bool GetKeyUp(SDL_Keycode userKey);
	bool GetKeyDown(SDL_Keycode userKey);
	bool GetKeyHeld(SDL_Keycode userKey);
private:
	SDL_Event* gameEvent;
	int m_keys[SDL_SCANCODE_ENDCALL] = { 0 };
};

