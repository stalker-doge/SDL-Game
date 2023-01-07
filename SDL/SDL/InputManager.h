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
	bool GetMouseUp(int userButton);
	bool GetMouseDown(int userButton);
	bool GetMouseHeld(int userButton);
	int GetMouseX();
	int GetMouseY();
	
	void Destroy();
private:
	InputManager();
	InputManager(const InputManager&) = delete;
	int m_keys[SDL_SCANCODE_ENDCALL] = { 0 };
	std::vector<SDL_Keycode> m_keyUP;
	std::vector<SDL_Keycode> m_keyDOWN;
	static InputManager* s_instance;
	uint32_t mouse;
	int mouseX, mouseY;
	std::vector<int> m_mouseUP;
	std::vector<int> m_mouseDOWN;
	int m_mouseKeys[3] = { 0 };
};

