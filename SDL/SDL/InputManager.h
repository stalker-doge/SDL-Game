#pragma once
#include <SDL.h>
#include <vector>
class InputManager
{
public:
	~InputManager();
	static InputManager* Instance();
	void Update();
	bool GetKeyUp(SDL_Keycode userKey);
	bool GetKeyDown(SDL_Keycode userKey);
	bool GetKeyHeld(SDL_Keycode userKey);
	void Destroy();
private:
	InputManager();
	InputManager(const InputManager&) = delete;
	int m_keys[SDL_SCANCODE_ENDCALL] = { 0 };
	std::vector<SDL_Keycode> m_keyUP;
	std::vector<SDL_Keycode> m_keyDOWN;
	static InputManager* s_instance;
};

